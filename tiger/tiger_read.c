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

#include "tiger_priv.h"

TIGER_RECORD *tiger_read_next(TIGER *tiger, TIGER_FILE_TYPE type)
{
  TIGER_RECORD     *record = NULL;
  TIGER_FILE       *file   = NULL;
  TIGER_FILE_TYPES *file_type = NULL;

  DBUG_ENTER("tiger_read_next");

  if(!tiger) goto err1;

  if(!(record = tiger_record_init(tiger, type)))
    goto err1;

  file        = &tiger->files[type];
  file_type   = &tiger_file_types[type];

  if(!(record->record = fixed_read_next(file->fixed)))
    goto endoffile;

  DBUG_RETURN(record);

 endoffile:
  free(record);
 err1:
  DBUG_RETURN(NULL);
}
