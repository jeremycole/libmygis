/*
    Copyright (c) 2004, Jeremy Cole

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

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "mygis.h"

#include "dbf.h"
#include "dbf_priv.h"

char *dbf_record_field(DBF_RECORD *record, char *key)
{
  DBF *dbf = record->dbf;
  DBF_FIELD *field = dbf->fields;
  int i;

  for(i=0; i<dbf->numfields; i++, field++) {
    if(strcasecmp(field->name, key) == 0)
      return record->cells[i].data.character;
  }
  return NULL;
}
