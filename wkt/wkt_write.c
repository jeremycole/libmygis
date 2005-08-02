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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mygis.h"
#include "geometry.h"

#include "wkt.h"
#include "wkt_priv.h"

void wkt_write(GEOMETRY *geometry, FILE *f)
{
  POINT       *point;
  LINEARRING  *linearring;
  uint32      points, linearrings, i, j;

  DBUG_ENTER("wkt_write");

  if(!geometry) DBUG_VOID_RETURN;

  fprintf(f, "%s(", GEOMETRY_TYPES[geometry->type]);
  switch(geometry->type) {
  case T_POINT:
    fprintf(f, "%F %F",
	    geometry->value.point->point->x,
	    geometry->value.point->point->y);
    break;

  case T_LINESTRING:
    point = geometry->value.linestring->points;
    for(i=0;i<(points=geometry->value.linestring->items);i++,point++) {
      fprintf(f, "%F %F%s",
	      point->x, point->y,
	      i<points-1?",  ":"");
    }
    break;

  case T_POLYGON:
    linearring = geometry->value.polygon->linearrings;
    for(j=0;j<(linearrings=geometry->value.polygon->items);j++,linearring++) {
      fprintf(f, "(");
      point = linearring->points;
      for(i=0;i<(points=linearring->items);i++,point++) {
        fprintf(f, "%F %F%s",
		point->x, point->y,
		i<points-1?",  ":"");
      }
      fprintf(f, ")%s", j<linearrings-1?", ":"");
    }
    break;
  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_MULTIPOLYGON:
  case T_GEOMETRYCOLLECTION:
  default:
    fprintf(f, "...");
    break;
  }
  fprintf(f, ")");

  DBUG_VOID_RETURN;
}
