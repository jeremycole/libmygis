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

uint32 wkb_size(GEOMETRY *geometry)
{
  POINT       *point;
  LINEARRING  *linearring;
  GEOMETRY_POLYGON *polygon;
  uint32      points, linearrings, polygons;
  uint32      i, j, k;
  uint32      size = 0;

  DBUG_ENTER("wkb_size");

  if(!geometry) DBUG_VOID_RETURN;

  /* minimalistic WKB header */
  size += WKB_SZ_BYTEORDER; /* byte order */
  size += WKB_SZ_TYPE; /* object type */
  
  switch(geometry->type) {
  case T_POINT:
    size += WKB_SZ_POINT;
    break;

  case T_LINESTRING:
    size += WKB_SZ_NUMITEMS; /* number of points */
    size += WKB_SZ_POINT * geometry->value.linestring->items;
    break;

  case T_POLYGON:
    size += WKB_SZ_NUMITEMS; /* number of linearrings */
    linearring  = geometry->value.polygon->linearrings;
    linearrings = geometry->value.polygon->items;
    for(j=0;j<linearrings;j++,linearring++) {
      size += WKB_SZ_NUMITEMS; /* number of points */
      size += WKB_SZ_POINT * linearring->items;
    }
    break;

  case T_MULTIPOLYGON:
    size += WKB_SZ_NUMITEMS; /* number of polygons */
    polygon  = geometry->value.multipolygon->polygons;
    polygons = geometry->value.multipolygon->items;
    for(k=0; k<polygons; k++, polygon++)
    {
      size += WKB_SZ_BYTEORDER; /* byte order */
      size += WKB_SZ_TYPE;      /* object type */
      size += WKB_SZ_NUMITEMS;  /* number of linearrings */
      linearring  = polygon->linearrings;
      linearrings = polygon->items;
      for(j=0;j<linearrings;j++,linearring++)
      {
        size += WKB_SZ_NUMITEMS; /* number of points */
        size += WKB_SZ_POINT * linearring->items;
      }
    }
    break;

  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_GEOMETRYCOLLECTION:
  default:
    fprintf(stderr, "oops, can't estimate size of unknown type.\n");
    break;
  }

  DBUG_RETURN(size);
}