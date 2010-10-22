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

#include "mygis_priv.h"
#include "geometry.h"
#include "e00/e00.h"
#include "wkt/wkt.h"

int main(int argc, char **argv)
{
  E00 *e00;
  GEOMETRY *geo;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  DBUG_PUSH("d:t");

  if(argc != 2)
  {
    printf("usage %s <arcfile.e00>\n", argv[0]);
    DBUG_RETURN(-1);
  }

  if(!(e00 = e00_init(0)))
  {
    printf("Couldn't init\n");
    DBUG_RETURN(-2);
  }

  if(e00_open(e00, argv[1], 'r') < 0)
  {
    printf("Couldn't open\n");
    DBUG_RETURN(-3);
  }

  e00_dump(e00);

  /*
  while((geo = e00_read_next(e00)))
  {
    geometry_dump(geo, 1);
    geometry_free(geo);
  }
  */

  e00_close(e00);
  e00_free(e00);

  DBUG_RETURN(0);
}
