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

#include <stdio.h>

#include "mygis.h"
#include "geometry.h"
#include "shp/shp.h"
#include "wkt/wkt.h"

int main(int argc, char **argv)
{
  SHP *shp;
  GEOMETRY *geo;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  DBUG_PUSH("d:t");

  if(argc != 2)
  {
    printf("usage %s <shapefile.shp>\n", argv[0]);
    DBUG_RETURN(-1);
  }

  if(!(shp = shp_init(0)))
  {
    printf("Couldn't init\n");
    DBUG_RETURN(-2);
  }

  if(shp_open(shp, argv[1], 'r') < 0)
  {
    printf("Couldn't open\n");
    DBUG_RETURN(-3);
  }

  shp_dump(shp);

  while((geo = shp_read_next(shp)))
  {
    geometry_dump(geo, 1);
    geometry_free(geo);
  }

  shp_close(shp);
  shp_free(shp);

  DBUG_RETURN(0);
}
