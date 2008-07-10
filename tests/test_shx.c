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
#include "shp/shx.h"

int main(int argc, char **argv)
{
  SHX *shx;
  SHX_RECORD *rec;

  int i;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  DBUG_PUSH("d:t");

  if(argc != 2)
  {
    printf("usage %s <shapefile.shx>\n", argv[0]);
    DBUG_RETURN(-1);
  }

  if(!(shx = shx_init(0)))
  {
    printf("Couldn't init\n");
    DBUG_RETURN(-2);
  }

  if(shx_open(shx, argv[1], 'r') < 0)
  {
    printf("Couldn't open\n");
    DBUG_RETURN(-3);
  }

  shx_dump(shx);

  for(i=0; i<100; i+=10)
  {
    shx_seek_record(shx, i);
    rec = shx_read_next(shx);
    shx_record_dump(rec, 1);
    shx_record_free(rec);
  }

  /*
  while(rec = shx_read_next(shx))
  {
    shx_record_dump(rec, 1);
    shx_record_free(rec);
  }
  */
  shx_close(shx);
  shx_free(shx);

  DBUG_RETURN(0);
}
