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

#include "mygis.h"
#include "geometry.h"
#include "shapefile.h"

int main(int argc, char **argv)
{
  SHAPEFILE *sha;
  SHAPEFILE_RECORD *rec;

  int rc;
  int i, max;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  DBUG_PUSH("d:t");

  if(argc != 2) {
    printf("usage %s <shapefile>\n", argv[0]);
    DBUG_RETURN(-1);
  }

  if(!(sha = shapefile_init(0))) {
    printf("Couldn't init\n");
    DBUG_RETURN(-2);
  }

  if((rc= shapefile_open(sha, argv[1], 'r')) < 0) {
    printf("Couldn't open\n");
    DBUG_RETURN(-3);
  }

  shapefile_dump(sha);

  max = sha->dbf->numrecords < 100 ? sha->dbf->numrecords : 100;

  for(i=1; i<max; i+=10) {
    shapefile_seek_record(sha, i);
    if((rec = shapefile_read_next(sha))) {
      shapefile_record_dump(rec);
      shapefile_record_free(rec);
    } else {
      printf("Error reading record\n");
      return 4;
    }
    printf("\n\n\n");
  }

  shapefile_close(sha);
  shapefile_free(sha);

  DBUG_RETURN(0);
}
