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

#include "wkb_priv.h"

char *wkb_write(GEOMETRY *geometry, char *wkb)
{
  POINT       *point;
  LINEARRING  *linearring;
  GEOMETRY_POLYGON *polygon;
  uint32      points, linearrings, polygons;
  uint32      i, j, k;
  char *cur;

  DBUG_ENTER("wkb_write");

  if(!geometry) DBUG_RETURN(NULL);
  
  if(!wkb) {
    if(!(wkb = cur = (char *)malloc(wkb_size(geometry)))) {
      DBUG_RETURN(NULL);
    }
  }

  /* minimalistic WKB header */
  MYGIS_WRITE_BYTE(cur, 1); cur += WKB_SZ_BYTEORDER; /* byte order */
  MYGIS_WRITE_UINT32_LE(cur, geometry->type); cur += WKB_SZ_TYPE; /* object type */
  
  switch(geometry->type) {
  case T_POINT:
    MYGIS_WRITE_DOUBLE_LE(cur, geometry->value.point->point->x);
    cur += SZ_DOUBLE;
    
    MYGIS_WRITE_DOUBLE_LE(cur, geometry->value.point->point->y);
    cur += SZ_DOUBLE;
    break;

  case T_LINESTRING:
    MYGIS_WRITE_UINT32_LE(cur, geometry->value.linestring->items);
    cur += WKB_SZ_NUMITEMS; /* number of points */
    
    point = geometry->value.linestring->points;
    for(i=0;i<(points=geometry->value.linestring->items);i++,point++) {
      MYGIS_WRITE_DOUBLE_LE(cur, point->x);
      cur += SZ_DOUBLE;
      MYGIS_WRITE_DOUBLE_LE(cur, point->y);
      cur += SZ_DOUBLE;
    }
    break;

  case T_POLYGON:
    MYGIS_WRITE_UINT32_LE(cur, geometry->value.polygon->items);
    cur += WKB_SZ_NUMITEMS; /* number of linearrings */
    linearring  = geometry->value.polygon->linearrings;
    linearrings = geometry->value.polygon->items;
    for(j=0; j<linearrings; j++, linearring++) {
      MYGIS_WRITE_UINT32_LE(cur, linearring->items);
      cur += WKB_SZ_NUMITEMS; /* number of points */
      point  = linearring->points;
      points = linearring->items;
      for(i=0; i<points; i++, point++) {
        MYGIS_WRITE_DOUBLE_LE(cur, point->x);
        cur += SZ_DOUBLE;
        MYGIS_WRITE_DOUBLE_LE(cur, point->y);
        cur += SZ_DOUBLE;
      }
    }
    break;

  case T_MULTIPOLYGON:
    MYGIS_WRITE_UINT32_LE(cur, geometry->value.multipolygon->items);
    cur += WKB_SZ_NUMITEMS; /* number of polygons */
    polygon  = geometry->value.multipolygon->polygons;
    polygons = geometry->value.multipolygon->items;
    for(k=0; k<polygons; k++, polygon++)
    {
      MYGIS_WRITE_BYTE(cur, 1); cur += WKB_SZ_BYTEORDER; /* byte order */
      MYGIS_WRITE_UINT32_LE(cur, WKB_POLYGON); cur += WKB_SZ_TYPE; /* object type */
      MYGIS_WRITE_UINT32_LE(cur, polygon->items);
      cur += WKB_SZ_NUMITEMS; /* number of linearrings */
      linearring  = polygon->linearrings;
      linearrings = polygon->items;
      for(j=0; j<linearrings; j++, linearring++) {
        MYGIS_WRITE_UINT32_LE(cur, linearring->items);
        cur += WKB_SZ_NUMITEMS; /* number of points */
        point  = linearring->points;
        points = linearring->items;
        for(i=0; i<points; i++, point++) {
          MYGIS_WRITE_DOUBLE_LE(cur, point->x);
          cur += SZ_DOUBLE;
          MYGIS_WRITE_DOUBLE_LE(cur, point->y);
          cur += SZ_DOUBLE;
        }
      }
    }
    break;

  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_GEOMETRYCOLLECTION:
  default:
    fprintf(stderr, "oops, can't write wkb for unknown type.\n");
    break;
  }

  DBUG_RETURN(wkb);
}
