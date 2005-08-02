/*
    Copyright (c) 2004-2005, Jeremy Cole and others

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

#include "mygis.h"
#include "geometry.h"

#include "wkb.h"
#include "wkb_priv.h"

#include <stdlib.h>
#include <math.h>

POINT *_wkb_read_points(char *pos, uint32 num, char **next)
{
  POINT *p, *c;

  DBUG_ENTER("_wkb_read_points");

  if( (p=c=POINT_INIT(num)) ) {
    while(num--) {
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

  if( (p=c=LINEARRING_INIT(num)) ) {
    while(num--) {
      c->items  = items = MYGIS_READ_UINT32_LE(pos);
      c->points = _wkb_read_points((pos+SZ_UINT32), items, next);
      c->area   = fabs(area=geometry_linearring_area(c));
      c->type   = area<0?LR_ADD:(area>0?LR_SUBTRACT:LR_NONE);

      pos += WKB_SZ_NUMITEMS+(WKB_SZ_POINT*items);
      c++;
    }
    *next = pos;
    DBUG_RETURN(p);
  }
  DBUG_RETURN(NULL);
}

GEOMETRY *_wkb_read_geometry_point(WKB *wkb)
{
  GEOMETRY *geometry;
  char *next;

  DBUG_ENTER("_wkb_read_geometry_point");

  if( (geometry = geometry_init(T_POINT)) ) {
    if( (geometry->value.point = GEOMETRY_POINT_INIT) ) {
      geometry->value.point->point = _wkb_read_points(WKB_DATA(wkb->cur), 1, &next);
    } else {
      free(geometry);
      DBUG_RETURN(NULL);
    }

    wkb->cur = next;

    DBUG_RETURN(geometry);
  }
  DBUG_RETURN(NULL);
}


GEOMETRY *_wkb_read_geometry_linestring(WKB *wkb)
{
  GEOMETRY *geometry;
  char *next;
  int items;

  DBUG_ENTER("_wkb_read_geometry_linestring");

  if( (geometry = geometry_init(T_LINESTRING)) ) {
    if( (geometry->value.linestring = GEOMETRY_LINESTRING_INIT) ) {
      geometry->value.linestring->items = items = WKB_NUMITEMS(wkb->cur);
      geometry->value.linestring->points = _wkb_read_points(WKB_DATA(wkb->cur), items, &next);
    } else {
      free(geometry);
      DBUG_RETURN(NULL);
    }

    wkb->cur = next;

    DBUG_RETURN(geometry);
  }
  DBUG_RETURN(NULL);
}


GEOMETRY *_wkb_read_geometry_polygon(WKB *wkb)
{
  GEOMETRY *geometry;
  char *next;
  int items;

  DBUG_ENTER("_wkb_read_geometry_polygon");

  if( (geometry = geometry_init(T_POLYGON)) ) {
    if( (geometry->value.polygon = GEOMETRY_POLYGON_INIT) ) {
      geometry->value.polygon->items = items = WKB_NUMITEMS(wkb->cur);
      geometry->value.polygon->linearrings = _wkb_read_linearrings(WKB_DATA(wkb->cur), items, &next);
    } else {
      free(geometry);
      DBUG_RETURN(NULL);
    }

    wkb->cur = next;

    DBUG_RETURN(geometry);
  }
  DBUG_RETURN(NULL);
}

GEOMETRY *_wkb_read_geometry_multipoint(WKB *wkb)
{
  DBUG_ENTER("_wkb_read_geometry_multipoint");
  DBUG_RETURN(NULL);
}

GEOMETRY *_wkb_read_geometry_multilinestring(WKB *wkb)
{
  DBUG_ENTER("_wkb_read_geometry_multilinestring");
  DBUG_RETURN(NULL);
}

GEOMETRY *_wkb_read_geometry_multipolygon(WKB *wkb)
{
  DBUG_ENTER("_wkb_read_geometry_multipolygon");
  DBUG_RETURN(NULL);
}

GEOMETRY *wkb_read_next(WKB *wkb)
{
  DBUG_ENTER("wkb_read_next");
  if((!wkb) || ((wkb->cur - wkb->data) >= wkb->data_len))
    DBUG_RETURN(NULL);

  switch(WKB_TYPE(wkb->cur)) {
  case WKB_POINT:
    DBUG_RETURN(_wkb_read_geometry_point(wkb));
    break;
  case WKB_LINESTRING:
    DBUG_RETURN(_wkb_read_geometry_linestring(wkb));
    break;
  case WKB_POLYGON:
    DBUG_RETURN(_wkb_read_geometry_polygon(wkb));
    break;
  case WKB_MULTIPOINT:
  case WKB_MULTILINESTRING:
  case WKB_MULTIPOLYGON:
  case WKB_GEOMETRYCOLLECTION:
    printf("Got %s, but can't handle.\n", WKB_TYPES[WKB_TYPE(wkb->cur)]);
    DBUG_RETURN(NULL);
    break;

  default:
    printf("oops!  got type=%i \n", WKB_TYPE(wkb->cur));
    DBUG_RETURN(NULL);
  }

}
