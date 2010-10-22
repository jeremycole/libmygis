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
#include "dbf/dbf.h"

int main(int argc, char **argv)
{
  DBF *dbf;
  RECORD *rec;
  int i;

  if(argc != 2)
  {
    printf("usage %s <file.dbf>\n", argv[0]);
    return 0;
  }

  if(!(dbf = dbf_init(0)))
  {
    printf("Couldn't init\n");
    return 0;
  }

  if(dbf_open(dbf, argv[1], 'r') < 0)
  {
    printf("Couldn't open\n");
    return 0;
  }

  dbf_dump(dbf);

  for(i=0; (rec = dbf_read_next(dbf)); i++)
  {
    printf("Record %i:\n", i);
    record_dump(rec);
    record_free(rec);
  }

  dbf_close(dbf);
  dbf_free(dbf);

  return 0;
}
