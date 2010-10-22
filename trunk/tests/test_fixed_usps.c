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


#include "mygis_priv.h"
#include "fixed.h"

#include <stdio.h>
#include <stdlib.h>

FIXED_FILE_DEF usps_state[] = {
  {"COPYRIGHT DETAIL CODE", LEFT, FIXED_DISCARD, NOTNULL, 1},
  {"ZIP CODE", LEFT, FIXED_CHARACTER, NOTNULL, 5},
  {"UPDATE KEY NO", LEFT, FIXED_CHARACTER, NOTNULL, 10},
  {"ACTION CODE", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"RECORD TYPE CODE", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"CARRIER ROUTE ID", LEFT, FIXED_CHARACTER, NOTNULL, 4},
  {"STREET PRE DRCTN ABBREV", LEFT, FIXED_CHARACTER, NOTNULL, 2},
  {"STREET NAME", LEFT, FIXED_CHARACTER, NOTNULL, 28},
  {"STREET SUFFIX ABBREV", LEFT, FIXED_CHARACTER, NOTNULL, 4},
  {"STREET POST DRCTN ABBREV", LEFT, FIXED_CHARACTER, NOTNULL, 2},
  {"ADDR PRIMARY LOW NO", LEFT, FIXED_CHARACTER, NOTNULL, 10},
  {"ADDR PRIMARY HIGH NO", LEFT, FIXED_CHARACTER, NOTNULL, 10},
  {"ADDR PRMRY ODD EVEN CODE", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"BUILDING OR FIRM NAME", LEFT, FIXED_CHARACTER, NOTNULL, 40},
  {"ADDR SECONDARY ABBREV", LEFT, FIXED_CHARACTER, NOTNULL, 4},
  {"ADDR SECONDARY LOW NO", LEFT, FIXED_CHARACTER, NOTNULL, 8},
  {"ADDR SECONDARY HIGH NO", LEFT, FIXED_CHARACTER, NOTNULL, 8},
  {"ADDR SECNY ODD EVEN CODE", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"ZIP ADD ON LOW NO", LEFT, FIXED_CHARACTER, NOTNULL, 4},
  {"ZIP ADD ON HIGH NO", LEFT, FIXED_CHARACTER, NOTNULL, 4},
  {"BASE ALT CODE", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"LACS STATUS IND", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"GOVT BLDG IND", LEFT, FIXED_CHARACTER, NOTNULL, 1},
  {"FINANCE NO", LEFT, FIXED_CHARACTER, NOTNULL, 6},
  {"STATE ABBREV", LEFT, FIXED_CHARACTER, NOTNULL, 2},
  {"COUNTY NO", LEFT, FIXED_CHARACTER, NOTNULL, 3},
  {"CITY NAME", LEFT, FIXED_CHARACTER, NOTNULL, 28},
  {"CONGRESSIONAL DIST NO", LEFT, FIXED_CHARACTER, NOTNULL, 2},
  {"MUNICIPALITY CTYST KEY", LEFT, FIXED_CHARACTER, NOTNULL, 6},
  {"URBANIZATION CTYST KEY", LEFT, FIXED_CHARACTER, NOTNULL, 6},
  {"PREFD LAST LINE CTYST KEY", LEFT, FIXED_CHARACTER, NOTNULL, 6},
  {"FROM LATITUDE", LEFT, FIXED_FLOATING, NOTNULL, 10},
  {"FROM LONGITUDE", LEFT, FIXED_FLOATING, NOTNULL, 10},
  {"TO LATITUDE", LEFT, FIXED_FLOATING, NOTNULL, 10},
  {"TO LONGITUDE", LEFT, FIXED_FLOATING, NOTNULL, 10},
  {"FILLER", LEFT, FIXED_DISCARD, NOTNULL, 1}
};




int main(int argc, char **argv)
{
  FIXED *fixed;
  RECORD *record;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);
  DBUG_PUSH("d:t");

  if(!(fixed = fixed_init(0)))
  {
    fprintf(stderr, "Couldn't allocate FIXED\n");
    exit(1);
  }

  fixed_options(fixed)->gap = 1;

  fixed_file_def(fixed, usps_state, 36);

  fixed_dump(fixed);

  fixed_open(fixed, argv[1], 'r');
  while(record = fixed_read_next(fixed))
  {
    record_dump(record);
    record_free(record);
  }

  fixed_close(fixed);

  fixed_free(fixed);

  DBUG_RETURN(0);
}
