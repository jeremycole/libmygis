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

uint32 wkb_size(GEOMETRY *geometry)
{
  POINT       *point;
  LINEARRING  *linearring;
  uint32      points, linearrings, i, j;
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
    linearring = geometry->value.polygon->linearrings;
    for(j=0;j<(linearrings=geometry->value.polygon->items);j++,linearring++) {
      size += WKB_SZ_NUMITEMS; /* number of points */
      size += WKB_SZ_POINT * linearring->items;
    }
    break;
  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_MULTIPOLYGON:
  case T_GEOMETRYCOLLECTION:
  default:
    fprintf(stderr, "oops, can't estimate size of unknown type.\n");
    break;
  }

  DBUG_RETURN(size);
}