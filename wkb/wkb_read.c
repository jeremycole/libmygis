/*
    Copyright (c) 2004-2008, Jeremy Cole and others

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "wkb_priv.h"

POINT *_wkb_read_points(char *pos, uint32 num, char **next)
{
  POINT *p, *c;

  DBUG_ENTER("_wkb_read_points");

  if( (p=c=POINT_INIT(num)) )
  {
    while(num--)
    {
      c->x = MYGIS_READ_DOUBLE_LE(WKB_X(pos));
      c->y = MYGIS_READ_DOUBLE_LE(WKB_Y(pos));
      /* printf("read point: %F, %F\n", c->x, c->y); */
      pos += WKB_SZ_POINT;
      c++;
    }
    *next = pos;
    DBUG_RETURN(p);
  }

  DBUG_RETURN(NULL);
}

LINEARRING *_wkb_read_linearrings(char *pos, uint32 num, char **next)
{
  LINEARRING *p, *c;
  uint32 items;
  double area;

  DBUG_ENTER("_wkb_read_linearrings");

  if( (p=c=LINEARRING_INIT(num)) )
  {
    while(num--)
    {
      c->items  = items = MYGIS_READ_UINT32_LE(pos);
      c->points = _wkb_read_points((pos+SZ_UINT32), items, next);
      c->area   = fabs(area=geometry_linearring_area(c));
      c->type   = area<0?LR_EXTERIOR:(area>0?LR_INTERIOR:LR_UNKNOWN);

      pos += WKB_SZ_NUMITEMS+(WKB_SZ_POINT*items);
      c++;
    }
    *next = pos;
    DBUG_RETURN(p);
  }

  DBUG_RETURN(NULL);
}

GEOMETRY_POINT *_wkb_read_geometry_points(WKB *wkb, uint32 num)
{
  GEOMETRY_POINT *point, *points;
  char *next;
  uint32 i;

  DBUG_ENTER("_wkb_read_geometry_point");

  if(! (points = GEOMETRY_POINT_INIT_X(num)) )
    goto err0;

  for(i=0, point=points; i<num; i++, point++)
  {
    point->point = _wkb_read_points(WKB_DATA(wkb->cur), 1, &next);
    wkb->cur = next;
  }
  DBUG_RETURN(points);

 err0:
  DBUG_RETURN(NULL);
}


GEOMETRY_LINESTRING *_wkb_read_geometry_linestrings(WKB *wkb, uint32 num)
{
  GEOMETRY_LINESTRING *linestring, *linestrings;
  char *next;
  uint32 i;

  DBUG_ENTER("_wkb_read_geometry_linestring");

  if(! (linestrings = GEOMETRY_LINESTRING_INIT_X(num)) )
    goto err0;

  for(i=0, linestring=linestrings; i<num; i++, linestring++)
  {
    linestring->items  = WKB_NUMITEMS(wkb->cur);
    linestring->points = _wkb_read_points(WKB_DATA(wkb->cur), linestring->items, &next);

    wkb->cur = next;
  }

  DBUG_RETURN(linestrings);

 err0:
  DBUG_RETURN(NULL);
}

GEOMETRY_POLYGON *_wkb_read_geometry_polygons(WKB *wkb, uint32 num)
{
  GEOMETRY_POLYGON *polygon, *polygons;
  char *next;
  uint32 i;

  DBUG_ENTER("_wkb_read_polygon");

  if(! (polygons = GEOMETRY_POLYGON_INIT_X(num)) )
    goto err0;

  for(i=0, polygon=polygons; i<num; i++, polygon++)
  {
    polygon->items       = WKB_NUMITEMS(wkb->cur);
    polygon->linearrings = _wkb_read_linearrings(WKB_DATA(wkb->cur), polygon->items, &next);

    wkb->cur = next;
  }

  DBUG_RETURN(polygons);

 err0:
  DBUG_RETURN(NULL);
}

GEOMETRY_MULTIPOLYGON *_wkb_read_geometry_multipolygon(WKB *wkb)
{
  GEOMETRY_MULTIPOLYGON *mpolygon;
  char *next;
  uint32 i;

  DBUG_ENTER("_wkb_read_geometry_multipolygon");

  if(! (mpolygon = GEOMETRY_MULTIPOLYGON_INIT) )
    goto err0;

  mpolygon->items    = WKB_NUMITEMS(wkb->cur);
  wkb->cur= WKB_DATA(wkb->cur);
  mpolygon->polygons = _wkb_read_geometry_polygons(wkb, mpolygon->items);

  DBUG_RETURN(mpolygon);

 err0:
  DBUG_RETURN(NULL);
}


GEOMETRY_MULTIPOINT *_wkb_read_geometry_multipoint(WKB *wkb)
{
  DBUG_ENTER("_wkb_read_geometry_multipoint");
  DBUG_RETURN(NULL);
}

GEOMETRY_MULTILINESTRING *_wkb_read_geometry_multilinestring(WKB *wkb)
{
  DBUG_ENTER("_wkb_read_geometry_multilinestring");
  DBUG_RETURN(NULL);
}


GEOMETRY *wkb_read_next(WKB *wkb)
{
  DBUG_ENTER("wkb_read_next");
  GEOMETRY *geometry = NULL;

  if((!wkb) || ((wkb->cur - wkb->data) >= wkb->data_len))
    goto err0;

  switch(WKB_TYPE(wkb->cur))
  {
  case WKB_POINT:
    if(! (geometry = geometry_init(T_POINT)))
      goto err0;
    if(! (geometry->value.point = _wkb_read_geometry_points(wkb, 1)))
      goto err1;
    break;
  case WKB_LINESTRING:
    if(! (geometry = geometry_init(T_LINESTRING)))
      goto err0;
    if(! (geometry->value.linestring = _wkb_read_geometry_linestrings(wkb, 1)))
      goto err1;
    break;
  case WKB_POLYGON:
    if(! (geometry = geometry_init(T_POLYGON)))
      goto err0;
    if(! (geometry->value.polygon = _wkb_read_geometry_polygons(wkb, 1)))
      goto err1;
    break;
  case WKB_MULTIPOLYGON:
    if(! (geometry = geometry_init(T_MULTIPOLYGON)))
      goto err0;
    if(! (geometry->value.multipolygon = _wkb_read_geometry_multipolygon(wkb)))
      goto err1;
    break;
  case WKB_MULTIPOINT:
  case WKB_MULTILINESTRING:
  case WKB_GEOMETRYCOLLECTION:
    printf("Got %s, but can't handle.\n", WKB_TYPES[WKB_TYPE(wkb->cur)]);
    goto err0;
    break;

  default:
    printf("oops!  got type=%i \n", WKB_TYPE(wkb->cur));
    goto err0;
  }

  DBUG_RETURN(geometry);

 err1:
  free(geometry);
 err0:
  DBUG_RETURN(NULL);
}
