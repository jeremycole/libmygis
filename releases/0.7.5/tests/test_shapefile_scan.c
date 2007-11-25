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
  SHAPEFILE_SCAN *scan;
  SHAPEFILE_RECORD *rec;

  DBUG_PUSH("d:t");

  if(argc != 4) {
    printf("usage %s <shapefile> <key> <value>\n", argv[0]);
    return 0;
  }

  if(!(sha = shapefile_init(0))) {
    printf("Couldn't init\n");
    return 0;
  }

  if(shapefile_open(sha, argv[1], 'r') < 0) {
    printf("Couldn't open\n");
    return 0;
  }

  scan = shapefile_scan_init(sha, &compare_string_ci_eq, argv[2], argv[3]);

  while((rec = shapefile_scan_read_next(scan))) {
    shapefile_record_dump(rec);
    shapefile_record_free(rec);
    printf("\n\n\n");
  }

  shapefile_scan_free(scan);

  shapefile_close(sha);
  shapefile_free(sha);

  return 0;
}
