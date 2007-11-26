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

TIGER *tiger_init(int flags)
{
  TIGER            *tiger     = NULL;
  TIGER_FILE       *file      = NULL;
  TIGER_FILE_TYPES *file_type = NULL;
  FIXED_FILE_DEF   *file_def  = NULL;
  uint type, field;

  DBUG_ENTER("tiger_init");

  if(!(tiger = TIGER_INIT))
    goto err1;

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file        = &tiger->files[type];
    file_type   = &tiger_file_types[type];

    file->type  = file_type->type;
    file->flags = flags;
    if(!(file->fixed = fixed_init(0))) {
      printf("Couldn't allocate fixed for file %i\n", type);
      goto err2;
    }
    fixed_file_def(file->fixed, file_type->file_def, file_type->num_fields);
  }

  DBUG_RETURN(tiger);

 err2:
  free(tiger);
 err1:
  DBUG_RETURN(NULL);
}

int tiger_open(TIGER *tiger, char *basename, char mode)
{
  TIGER_FILE       *file      = NULL;
  TIGER_FILE_TYPES *file_type = NULL;
  uint type;
  char *filename;

  DBUG_ENTER("tiger_open");

  if(!(filename = (char *) malloc(strlen(basename)+10)))
    DBUG_RETURN(1);

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file      = &tiger->files[type];
    file_type = &tiger_file_types[type];
    strcpy(filename, basename);
    strcat(filename, file_type->file_ext[0]);

    DBUG_PRINT("info", ("Attempting to open file %s", filename));
    if(fixed_open(file->fixed, filename, mode) != -1) {
      file->is_available= 1;
    } else {
      file->is_available= 0;
    }
  }

  free(filename); 
  DBUG_RETURN(0);
}

void tiger_dump(TIGER *tiger)
{
  TIGER_FILE *file = NULL;
  uint type;
      
  DBUG_ENTER("tiger_dump");

  printf("TIGER Record Types Available: ");
  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file = &tiger->files[type];
    if(file->is_available)
      printf("%s", tiger_file_types[type].record_type);
  }
  printf("\n\n");

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file = &tiger->files[type];
    printf("Record Type %s, %s\n", tiger_file_types[type].record_type,
           tiger_file_types[type].name);
    fixed_dump(file->fixed);
  }
  	        
  DBUG_VOID_RETURN;
}

void tiger_close(TIGER *tiger)
{
}

void tiger_free(TIGER *tiger)
{
  TIGER_FILE *file = NULL;
  uint type;

  DBUG_ENTER("tiger_free");

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file = &tiger->files[type];
    fixed_free(file->fixed);
  }

  free(tiger);

  DBUG_VOID_RETURN;
}

TIGER_RECORD *tiger_record_init(TIGER *tiger, TIGER_FILE_TYPE type)
{
  TIGER_RECORD *record;

  DBUG_ENTER("tiger_record_init");

  if(!(record = TIGER_RECORD_INIT))
    DBUG_RETURN(NULL);

  record->tiger  = tiger;
  record->type   = type;
  record->record = NULL;

  DBUG_RETURN(record);
}

void tiger_record_dump(TIGER_RECORD *record)
{
  DBUG_ENTER("tiger_record_dump");
  record_dump(record->record);
  DBUG_VOID_RETURN;
}

void tiger_record_free(TIGER_RECORD *record)
{
  DBUG_ENTER("tiger_record_free");
  if(!record) DBUG_VOID_RETURN;
  record_free(record->record);
  free(record);
  DBUG_VOID_RETURN;
}
