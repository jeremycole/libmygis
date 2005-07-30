/*
    Copyright (c) 2004, Jeremy Cole

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "geometry.h"

const char GEOMETRY_TYPES[GEOMETRY_TYPE_MAX][20] = {
  {"NULL"},
  {"POINT"},  
  {"LINESTRING"},
  {"POLYGON"},   
  {"MULTIPOINT"},
  {"MULTILINESTRING"},
  {"MULTIPOLYGON"},   
  {"GEOMETRYCOLLECTION"}
};

GEOMETRY *geometry_init(GEOMETRY_TYPE type)
{
  GEOMETRY *geometry;

  DBUG_ENTER("geometry_init");

  if( (geometry = GEOMETRY_INIT) ) {
    geometry->type = type;
    DBUG_RETURN(geometry);
  }
  DBUG_RETURN(NULL);
}

void geometry_dump(GEOMETRY *geometry, int level) {
  LINEARRING  *linearring;
  POINT *point;
  uint32      i, j;

  DBUG_ENTER("geometry_dump");

  if(!geometry) {
    fprintf(stderr, "No geometry specified!\n");
    DBUG_VOID_RETURN;
  }

  switch(geometry->type) {
  case T_POINT:
    printf("POINT: %12.6f, %12.6f\n",
	   geometry->value.point->point->x,
	   geometry->value.point->point->y);
    break;

  case T_LINESTRING:
    printf("LINESTRING: %5i point%s\n",
	   geometry->value.linestring->items,
	   geometry->value.linestring->items>1?"s":""
	   );
    if(level > 1) {
      for(point=geometry->value.linestring->points,i=0; i<geometry->value.linestring->items; point++,i++) {
	printf("  POINT %5i: %12.6f, %12.6f\n", i, point->x, point->y);
      }
    }
    break;

  case T_POLYGON:
    printf("POLYGON: %5i linearring%s\n",
	   geometry->value.polygon->items,
	   geometry->value.polygon->items>1?"s":"");
    if(level > 0) {
      linearring = geometry->value.polygon->linearrings;
      for(j=0;j<(geometry->value.polygon->items);j++,linearring++) {
	printf("  %sLINEARRING %5i: %5i point%s, %12.6f area\n",
	       (linearring->type==LR_ADD)?"+":((linearring->type==LR_SUBTRACT)?"-":((linearring->type==LR_NONE)?"=":"*")),
	       j,
	       linearring->items,
	       linearring->items>1?"s":"",
	       linearring->area);
	if(level > 2) {
	  for(point=linearring->points,i=0; i<linearring->items; point++,i++) {
	    printf("    POINT %5i: %12.6f, %12.6f\n", i, point->x, point->y);
	  }
	}
		   
      }
    }
    break;

  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_MULTIPOLYGON:
  case T_GEOMETRYCOLLECTION:
  default:
    printf("UNKNOWN: Uknown object: Type %i: %s.\n",
           geometry->type, geometry->type<GEOMETRY_TYPE_MAX?GEOMETRY_TYPES[geometry->type]:"object type out of range");
  }

  DBUG_VOID_RETURN;
}

void geometry_free(GEOMETRY *geometry)
{
  LINEARRING  *linearring;
  uint32      j;

  DBUG_ENTER("geometry_free");

  if(!geometry) DBUG_VOID_RETURN;

  /*
  for(i=0;i<geometry->info.items;i++) {
    free(geometry->info.values[i]->name);
    free(geometry->info.values[i]->value);
    free(geometry->info.values[i]);
  }
  */
               
  switch(geometry->type) {
  case T_POINT:
    free(geometry->value.point->point);
    free(geometry->value.point);
    break;
  case T_LINESTRING:
    free(geometry->value.linestring->points);
    free(geometry->value.linestring);
    break;
  case T_POLYGON:
    linearring = geometry->value.polygon->linearrings;
    for(j=0;j<(geometry->value.polygon->items);j++,linearring++) {
      free(linearring->points);
    }
    free(geometry->value.polygon->linearrings);
    free(geometry->value.polygon);
    break;
  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_MULTIPOLYGON:
  case T_GEOMETRYCOLLECTION:
  default:
    DBUG_PRINT("leak", ("Object %s was allocated that can't be freed.\n",
			GEOMETRY_TYPES[geometry->type]));
  }
  free(geometry);
  DBUG_VOID_RETURN;
}

/* 

Point in Polygon test

http://geometryalgorithms.com/Archive/algorithm_0103/algorithm_0103.htm

*/


double geometry_linearring_area(LINEARRING *linearring) {
  POINT *s, *p, *r;
  double area;
  uint32 i;

  DBUG_ENTER("geometry_linearring_area");

  /* http://astronomy.swin.edu.au/~pbourke/geometry/clockwise/ */
  /* clockwise = add */
  /* counterclockwise = subtract */

  s=p=r=linearring->points;
  for(area=0.0,p++,i=0; i < linearring->items-1; p++,r++,i++) {
    area += r->x*p->y - p->x*r->y;
  }
  area /= 2;

  DBUG_RETURN(area);
}
