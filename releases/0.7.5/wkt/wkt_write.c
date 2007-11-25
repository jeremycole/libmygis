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

void wkt_write(GEOMETRY *geometry, PROJECTION *projection, FILE *f)
{
  POINT       *point;
  POINT       tpoint;
  LINEARRING  *linearring;
  GEOMETRY_POLYGON *polygon;
  uint32      points, linearrings, polygons;
  uint32      i, j, k;

  DBUG_ENTER("wkt_write");

  if(!geometry) DBUG_VOID_RETURN;

  /* fprintf(f, "%s(", GEOMETRY_TYPES[geometry->type]); */
  switch(geometry->type) {
  case T_POINT:
    fprintf(f, "POINT(");
    point = geometry->value.point->point;
    tpoint= geometry_point_reproject(point, projection);

    fprintf(f, "%F %F",
	    tpoint.x,
	    tpoint.y);
    break;

  case T_LINESTRING:
    fprintf(f, "LINESTRING(");
    point  = geometry->value.linestring->points;
    points = geometry->value.linestring->items;
    for(i=0;i<points;i++,point++) {
      tpoint= geometry_point_reproject(point, projection);

      fprintf(f, "%F %F%s",
	      tpoint.x, tpoint.y,
	      i<points-1?",  ":"");
    }
    break;

  case T_POLYGON:
    linearring  = geometry->value.polygon->linearrings;
    linearrings = geometry->value.polygon->items;
    fprintf(f, "POLYGON(");
    for(j=0; j<linearrings; j++, linearring++) {
      fprintf(f, "(");
      point  = linearring->points;
      points = linearring->items;
      for(i=0; i<points; i++, point++) {
        tpoint= geometry_point_reproject(point, projection);

        fprintf(f, "%F %F%s",
          tpoint.x, tpoint.y,
          i<points-1?",  ":"");
      }
      fprintf(f, ")%s", j<linearrings-1?", ":"");
    }
    break;

  case T_MULTIPOLYGON:
    polygon  = geometry->value.multipolygon->polygons;
    polygons = geometry->value.multipolygon->items;
    fprintf(f, (polygons<=1)?"POLYGON(":"MULTIPOLYGON(");
    for(k=0; k<polygons; k++, polygon++)
    {
      linearring  = polygon->linearrings;
      linearrings = polygon->items;
      if(polygons>1) fprintf(f, "(");
      for(j=0;j<linearrings;j++,linearring++)
      {
        point  = linearring->points;
        points = linearring->items;
        fprintf(f, "(");
        for(i=0; i<points; i++, point++)
        {
          tpoint= geometry_point_reproject(point, projection);
  
          fprintf(f, "%F %F%s",
            tpoint.x, tpoint.y,
            i<points-1?",  ":"");
        }
        fprintf(f, ")%s", j<linearrings-1?", ":"");
      }
      if(polygons>1) fprintf(f, ")%s", k<polygons-1?", ":"");
    }
    break;


  case T_MULTIPOINT:
  case T_MULTILINESTRING:
  case T_GEOMETRYCOLLECTION:
  default:
    fprintf(f, "...");
    break;
  }
  fprintf(f, ")");

  DBUG_VOID_RETURN;
}
