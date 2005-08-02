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

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "dbf.h"
#include "dbf_priv.h"

int _dbf_read_header(DBF *dbf) {
  DBF_FIELD *field;
  int i;
  ssize_t count;
  char temp[32];

  DBUG_ENTER("_dbf_read_header");

  dbf_seek(dbf, DBF_POS_FILE_HEADER);

  if((count=read(dbf->fd, dbf->header, DBF_LEN_FILE_HEADER)) < DBF_LEN_FILE_HEADER) {
    fprintf(stderr, "DBF: Error reading header: read only %i bytes, expected %i bytes\n", count, DBF_LEN_FILE_HEADER);
    close(dbf->fd);
    DBUG_RETURN(-2);
  }

  dbf->numfields     = (DBF_HDR_LENHEADER(dbf->header)-33)/32;
  dbf->version       = DBF_HDR_VERSION(dbf->header);
  dbf->numrecords    = DBF_HDR_NUMRECORDS(dbf->header);
  dbf->record_length = 0;

  if(dbf->version != 0x03) {
    fprintf(stderr, "DBF: Unsupported dBase file version 0x%02x\n", 
            dbf->version);
    close(dbf->fd);
    DBUG_RETURN(-3);
  }

  field = dbf->fields = DBF_FIELD_INIT(dbf->numfields);

  for(i=0; i<dbf->numfields; i++, field++) {
    if((count=read(dbf->fd, temp, DBF_LEN_FIELD)) < DBF_LEN_FIELD) {
      fprintf(stderr, "DBF: Error reading field!\n");
      DBUG_RETURN(-3);
    }

    strncpy(field->name, DBF_FLD_NAME(temp), 10);
    field->name[10] = '\0';
    field->type   = DBF_FLD_TYPE(temp);
    field->length = DBF_FLD_LEN(temp);
    switch(field->type) {
    case CHARACTER:
    case NUMBER:
    case FLOATING:
      dbf->record_length += field->size = field->length;
      break;

    case LOGICAL:
      dbf->record_length += field->size = 1;
      break;
      
    case DATE:
      dbf->record_length += field->size = 8; 
      break;

    case GENERAL:
    case MEMO:
    case PICTURE:
      fprintf(stderr, "DBF: Unsupported field type %c!  Please ask for support from the author!\n", field->type);
      DBUG_RETURN(-4);

    default:
      fprintf(stderr, "DBF: Unknown field type %c!\n", field->type);
      DBUG_RETURN(-4);
    }
  }

  if(!(dbf->record_buffer = (char *)malloc(dbf->record_length+2)))
    DBUG_RETURN(-5);

  /* set the last byte to \0 so that e.g. strndup doesn't over-read */
  dbf->record_buffer[dbf->record_length+1] = '\0';

  DBUG_RETURN(0);
}

DBF_RECORD *dbf_read_next(DBF *dbf)
{
  DBF_RECORD *record = NULL;
  DBF_FIELD *field;
  DBF_CELL *cell;
  ssize_t count;
  char *buf, *cur, *tmp;
  int i;
  uint32 len = dbf->record_length;

  DBUG_ENTER("dbf_read_next");

  buf = cur = memset(dbf->record_buffer, 0, dbf->record_length+1);

  if((count=read(dbf->fd, buf, dbf->record_length+1)) < dbf->record_length+1) {
    if(count == 1 && buf[0] == 0x1a) {
      goto endoffile;
    }
    fprintf(stderr, "DBF: Error reading record: read only %i bytes, expected %i bytes\n", count, dbf->record_length+1);
    close(dbf->fd);
    DBUG_RETURN(NULL);
  }

  record = DBF_RECORD_INIT;
  record->dbf    = dbf;
  record->cells = cell = DBF_CELL_INIT(dbf->numfields);
  record->status = cur[0]; cur++;

  for(field=dbf->fields, i=0; i<dbf->numfields; field++, cell++, i++) {
    cell->field = field;
    switch(field->type) {
    case CHARACTER:
      if(!(cell->data.character = (char *)strndup(cur, field->size)))
        goto oom;
      mygis_trim(cell->data.character, field->size);
      break;
    case DATE:
      if(!(cell->data.date = (char *)strndup(cur, field->size)))
        goto oom;
      break;
    case NUMBER:
      if(!(tmp = (char *)strndup(cur, field->size)))
        goto oom;
      cell->data.number = atoi(tmp);
      free(tmp);
      break;
    case FLOATING:
      if(!(tmp = (char *)strndup(cur, field->size)))
        goto oom;
      cell->data.floating = atof(tmp);
      free(tmp);
      break;
    case LOGICAL:
      cell->data.logical = cur[0];
      break;
    case GENERAL:
    case MEMO:
    case PICTURE:
      fprintf(stderr, "Unsupported field type %c!  Please ask for support from the author!\n", field->type);
      return NULL;
    default:
      fprintf(stderr, "Unknown field type %c!\n", field->type);
      return NULL;
    }
    cur += field->size;
  }

 endoffile:
  dbf->position++;
  DBUG_RETURN(record);

 oom:
  fprintf(stderr, "DBF: Out of memory!\n");
  DBUG_RETURN(NULL);
}
