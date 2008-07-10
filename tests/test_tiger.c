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


#include "mygis.h"
#include "tiger/tiger.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  TIGER *tiger;
  TIGER_RECORD *record;
  uint x;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  //DBUG_PUSH("d:t");

  if(!(tiger = tiger_init(0))) {
    fprintf(stderr, "Couldn't allocate TIGER\n");
    exit(1);
  }

  tiger_open(tiger, argv[1], 'r');
  tiger_dump(tiger);

  for(x=0; x<5 && (record = tiger_read_next(tiger, RT2)); x++) {
    tiger_record_dump(record);
    tiger_record_free(record);
  }

  tiger_free(tiger);

  DBUG_RETURN(0);
}
