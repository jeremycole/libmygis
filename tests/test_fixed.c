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
#include "fixed.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FIXED *fixed;
  FIXED_RECORD *record;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  /*DBUG_PUSH("d:t");*/

  if(!(fixed = fixed_init(0))) {
    fprintf(stderr, "Couldn't allocate FIXED\n");
    exit(1);
  }
  
  fixed_options(fixed)->gap = 1;

  fixed_append(fixed, fixed_field_new("name",   RIGHT, CHARACTER, NOTNULL, 20));
  fixed_append(fixed, fixed_field_new("age",    LEFT,  NUMBER,    NOTNULL,  3));
  fixed_append(fixed, fixed_field_new("height", LEFT,  FLOATING,  NOTNULL, 10));
  fixed_append(fixed, fixed_field_new("weight", LEFT,  FLOATING,  NOTNULL, 10));
  fixed_dump(fixed);

  fixed_open(fixed, argv[1], 'r');
  while(record = fixed_read_next(fixed)) {
    fixed_record_dump(record);
    fixed_record_free(record);
  }

  fixed_close(fixed);
  
  fixed_free(fixed);

  DBUG_RETURN(0);
}
