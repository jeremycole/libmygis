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

#include "shp_priv.h"

int _shp_read_header(SHP *shp)
{
  DBUG_ENTER("_shp_read_header");

  shp_seek(shp, SHP_POS_HEADER);

  if(!(shp->header = _sh_header_read(shp->fd)))
  {
    close(shp->fd);
    DBUG_RETURN(-2);
  }

  DBUG_RETURN(0);
}

POINT *_shp_read_points(char *pos, uint32 num)
{
  POINT *p, *c;

  DBUG_ENTER("_shp_read_points");
  DBUG_PRINT("args", ("pos=0x%08x num=%i", pos, num));

  if( (p=c=POINT_INIT(num)) )
  {
    while(num--)
    {
      c->x = MYGIS_READ_DOUBLE_LE(SHP_X(pos));
      c->y = MYGIS_READ_DOUBLE_LE(SHP_Y(pos));
      c++;
      pos += SHP_SZ_POINT;
    }
    DBUG_RETURN(p);
  }

  DBUG_RETURN(NULL);
}


LINEARRING *_shp_read_linearring(char *pos, uint32 size)
{
  LINEARRING *lr;

  DBUG_ENTER("_shp_read_linearring");
  DBUG_PRINT("args", ("pos=0x%08x size=%i", pos, size));

  if( (lr=LINEARRING_INIT(1)) )
  {
    lr->items = size;
    lr->points = _shp_read_points(pos, size);
    DBUG_RETURN(lr);
  }

  DBUG_RETURN(NULL);
}


LINEARRING *_shp_read_linearrings(char *pos, uint32 *parts,
				  uint32 num_parts, uint32 num_points)
{
  LINEARRING *lr, *lrc;
  double area;

  DBUG_ENTER("_shp_read_linearrings");
  DBUG_PRINT("args", ("pos=0x%08x parts=0x%08x num_parts=%i num_points=%i",
                      pos, parts, num_parts, num_points));

  if( (lr=lrc=LINEARRING_INIT(num_parts)) )
  {
    for(;num_parts--;lrc++,parts++)
    {
      lrc->type   = LR_UNKNOWN;
      lrc->items  = ((num_parts)?(MYGIS_READ_UINT32_LE((parts+1))):num_points)-(MYGIS_READ_UINT32_LE(parts));
      lrc->points = _shp_read_points(pos, lrc->items);
      lrc->area   = abs(area=geometry_linearring_area(lrc));
      lrc->type   = area<0.0?LR_EXTERIOR:(area>0.0?LR_INTERIOR:LR_UNKNOWN);

      pos += SHP_SZ_POINT*lrc->items;
    }
    DBUG_RETURN(lr);
  }

  DBUG_RETURN(NULL);
}


GEOMETRY *_shp_geometry_null()
{
  GEOMETRY *geometry;

  DBUG_ENTER("_shp_geometry_null");

  if( (geometry = geometry_init(T_NULL)) )
  {
    DBUG_RETURN(geometry);
  }

  DBUG_RETURN(NULL);
}

GEOMETRY *_shp_read_geometry_point(char *content)
{
  GEOMETRY *geometry;

  DBUG_ENTER("_shp_read_geometry_point");

  if( (geometry = geometry_init(T_POINT)) )
  {
    if( (geometry->value.point = GEOMETRY_POINT_INIT) )
    {
      if(!(geometry->value.point->point = _shp_read_points(content, 1)))
      {
	free(geometry);
	DBUG_RETURN(NULL);
      }
    } else {
      free(geometry);
      DBUG_RETURN(NULL);
    }
    DBUG_RETURN(geometry);
  }

  DBUG_RETURN(NULL);
}

GEOMETRY *_shp_read_geometry_multipoint(char *content)
{
  GEOMETRY *geometry;
  double *mbr;
  uint32 num_points;

  DBUG_ENTER("_shp_read_geometry_multipoint");

  mbr        = SHP_REC1_MBR(content);
  num_points = SHP_REC1_NUMPOINTS(content);

  if( (geometry = geometry_init(T_MULTIPOINT)) )
  {
    if( (geometry->value.multipoint = GEOMETRY_MULTIPOINT_INIT) )
    {
      geometry->mbr.min.x = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->mbr.min.y = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->mbr.max.x = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->mbr.max.y = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->value.multipoint->items = num_points;
      geometry->value.multipoint->points = _shp_read_points(SHP_REC1_POINTS(content), num_points);
    } else {
      free(geometry);
      DBUG_RETURN(NULL);
    }
    DBUG_RETURN(geometry);
  }

  DBUG_RETURN(NULL);
}

GEOMETRY *_shp_read_geometry_polyline(char *content)
{
  GEOMETRY *geometry;
  double *mbr;
  uint32 num_parts, num_points;

  DBUG_ENTER("_shp_read_geometry_polyline");

  mbr        = SHP_REC2_MBR(content);
  num_parts  = SHP_REC2_NUMPARTS(content);
  num_points = SHP_REC2_NUMPOINTS(content);

  if( (geometry = geometry_init(T_LINESTRING)) )
  {
    if( (geometry->value.linestring = GEOMETRY_LINESTRING_INIT) )
    {
      geometry->mbr.min.x = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->mbr.min.y = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->mbr.max.x = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->mbr.max.y = MYGIS_READ_DOUBLE_LE(mbr++);
      geometry->value.linestring->items = num_points;
      geometry->value.linestring->points = _shp_read_points(SHP_REC2_POINTS(content), num_points);
    } else {
      free(geometry);
      DBUG_RETURN(NULL);
    }
    DBUG_RETURN(geometry);
  }

  DBUG_RETURN(NULL);
}


GEOMETRY *_shp_read_geometry_polygon(char *content)
{
  GEOMETRY *geometry= NULL;
  GEOMETRY *return_geometry= NULL;
  double *mbr;
  uint32 num_parts, num_points;

  uint32 exterior= 0;
  uint32 item;
  LINEARRING *linearrings, *linearring, **linearringp;

  LINEARRING  **exterior_rings;
  uint32      *exterior_rings_items;

  uint32 last_exterior_ring;

  GEOMETRY_POLYGON *polygon;

  DBUG_ENTER("_shp_read_geometry_polygon");

  mbr        = SHP_REC2_MBR(content);
  num_parts  = SHP_REC2_NUMPARTS(content);
  num_points = SHP_REC2_NUMPOINTS(content);

  if(! (geometry = geometry_init(T_MULTIPOLYGON)) )
    goto err0;

  if(! (geometry->value.multipolygon = GEOMETRY_MULTIPOLYGON_INIT) )
    goto err1;

  geometry->mbr.min.x = MYGIS_READ_DOUBLE_LE(mbr++);
  geometry->mbr.min.y = MYGIS_READ_DOUBLE_LE(mbr++);
  geometry->mbr.max.x = MYGIS_READ_DOUBLE_LE(mbr++);
  geometry->mbr.max.y = MYGIS_READ_DOUBLE_LE(mbr++);

  linearrings = _shp_read_linearrings(SHP_REC2_POINTS(content), SHP_REC2_PARTS(content), num_parts, num_points);

  exterior_rings       = MYGIS_MALLOC_X(LINEARRING *, num_parts);
  exterior_rings_items = MYGIS_MALLOC_X(uint32,       num_parts);

  last_exterior_ring= 0;
  for(item=0, linearring=linearrings; item<num_parts; item++, linearring++)
  {
    if(linearring->type == LR_EXTERIOR)
    {
      if(exterior > 0)
        exterior_rings_items[exterior-1] = (item - last_exterior_ring);

      exterior_rings[exterior] = linearring;
      exterior++;
      last_exterior_ring = item;
    }
  }

  exterior_rings_items[exterior-1] = (item - last_exterior_ring);

  geometry->value.multipolygon->items = exterior;
  geometry->value.multipolygon->polygons =
    MYGIS_MALLOC_X(GEOMETRY_POLYGON, exterior);

  polygon= geometry->value.multipolygon->polygons;
  for(item=0, linearringp=exterior_rings; item<exterior; item++, linearringp++, polygon++)
  {
    polygon->items= exterior_rings_items[item];

    /* appears we need to dupe the memory at linearringp to avoid a double free later */
    polygon->linearrings= *linearringp;
  }

  return_geometry= geometry;

 err2:
  free(exterior_rings_items);
 err1:
  free(exterior_rings);
 err0:
  DBUG_RETURN(return_geometry);
}

GEOMETRY *shp_read_next(SHP *shp)
{
  GEOMETRY *geometry = NULL;
  uint32 count;
  uint32 record_number;
  uint32 content_length;
  uint32 type;
  char *content;

  DBUG_ENTER("shp_read_next");

  if(!shp)
    DBUG_RETURN(NULL);

  if((count=read(shp->fd, &record_number, SZ_UINT32)) != SZ_UINT32)
  {
    if(count > 0)
    {
      fprintf(stderr, "Couldn't read record number\n");
    }
    DBUG_RETURN(NULL);
  }

  if((count=read(shp->fd, &content_length, SZ_UINT32)) != SZ_UINT32)
  {
    fprintf(stderr, "Couldn't read content length\n");
    DBUG_RETURN(NULL);
  }

  if((count=read(shp->fd, &type, SZ_UINT32)) != SZ_UINT32)
  {
    fprintf(stderr, "Couldn't read shape type\n");
    DBUG_RETURN(NULL);
  }

  MYGIS_BE_UINT32(&record_number);
  MYGIS_BE_UINT32(&content_length);
  MYGIS_LE_UINT32(&type);

  /* content length is in 16-bit words, and we already got 'type' */
  content_length = (content_length*2)-SZ_UINT32;

  /*
  printf("record_number=%i ; content_length=%i\n",
	 record_number, content_length);
  */

  if((content=(char *)malloc(content_length)))
  {
    if((count=read(shp->fd, content, content_length)) != content_length)
    {
      fprintf(stderr, "Couldn't read entire record: read %i bytes, expected %i bytes\n", count, content_length);
      goto err;
    }
  } else {
    DBUG_RETURN(NULL);
  }

  switch(type)
  {
  case SHP_NULL:
    geometry = _shp_geometry_null();
    break;

  case SHP_POINT:
    geometry = _shp_read_geometry_point(content);
    break;

  case SHP_MULTIPOINT:
    geometry = _shp_read_geometry_multipoint(content);
    break;

  case SHP_POLYLINE:
    geometry = _shp_read_geometry_polyline(content);
    break;

  case SHP_POLYGON:
    geometry = _shp_read_geometry_polygon(content);
    break;

  case SHP_POINTZ:
  case SHP_POLYLINEZ:
  case SHP_POLYGONZ:
  case SHP_MULTIPOINTZ:
  case SHP_POINTM:
  case SHP_POLYLINEM:
  case SHP_POLYGONM:
  case SHP_MULTIPOINTM:
  case SHP_MULTIPATCH:
    printf("got type %s but can't yet handle it\n",
	   SHP_TYPES[type]);
    DBUG_RETURN(_shp_geometry_null());

  default:
    fprintf(stderr, "oops!  got type=%i (0x%08x)\n", type, type);
    DBUG_RETURN(NULL);
  }

  geometry_set_projection(geometry, shp->projection);

  shp->position++;
  free(content);
  DBUG_RETURN(geometry);

 err:
  free(content);
  DBUG_RETURN(NULL);
}
