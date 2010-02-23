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

#include "dbf_priv.h"

int _dbf_read_header(DBF *dbf)
{
  DBF_FIELD *field;
  int i;
  ssize_t count;
  char temp[32];

  DBUG_ENTER("_dbf_read_header");

  dbf_seek(dbf, DBF_POS_FILE_HEADER);

  if((count=read(dbf->fd, dbf->header, DBF_LEN_FILE_HEADER)) < DBF_LEN_FILE_HEADER)
  {
    fprintf(stderr, "DBF: Error reading header: read only %d bytes, expected %i bytes\n", count, DBF_LEN_FILE_HEADER);
    close(dbf->fd);
    DBUG_RETURN(-2);
  }

  dbf->numfields     = (DBF_HDR_LENHEADER(dbf->header)-33)/32;
  dbf->version       = DBF_HDR_VERSION(dbf->header);
  dbf->numrecords    = DBF_HDR_NUMRECORDS(dbf->header);
  dbf->record_length = 0;

  if(dbf->version != 0x03)
  {
    fprintf(stderr, "DBF: Unsupported dBase file version 0x%02x\n",
            dbf->version);
    close(dbf->fd);
    DBUG_RETURN(-3);
  }

  field = dbf->fields = DBF_FIELD_INIT(dbf->numfields);

  for(i=0; i<dbf->numfields; i++, field++)
  {
    if((count=read(dbf->fd, temp, DBF_LEN_FIELD)) < DBF_LEN_FIELD)
    {
      fprintf(stderr, "DBF: Error reading field!\n");
      DBUG_RETURN(-3);
    }

    strncpy(field->name, DBF_FLD_NAME(temp), 10);
    field->name[10]        = '\0';
    field->format[0]       = '\0';
    field->metadata.name   = field->name;
    field->metadata.format = field->format;

    field->type     = DBF_FLD_TYPE(temp);
    field->length   = DBF_FLD_LEN(temp);
    field->decimals = DBF_FLD_DECIMALS(temp);

    switch(field->type)
    {
    case DBF_CHARACTER:
      dbf->record_length += field->size = field->length;
      strcpy(field->format, "%s");
      field->metadata.data_type = CHARACTER;
      break;

    case DBF_NUMBER:
      /* if field->decimals >0, fall through to FLOATING */
      if(field->decimals == 0)
      {
        dbf->record_length += field->size = field->length;
        strcpy(field->format, "%lld");
        field->metadata.data_type = NUMBER;
        break;
      }

    case DBF_FLOATING:
      dbf->record_length += field->size = field->length;
      sprintf(field->format, "%%.%if", field->decimals);
      field->metadata.data_type = FLOATING;
      break;

    case DBF_LOGICAL:
      dbf->record_length += field->size = 1;
      strcpy(field->format, "%c");
      field->metadata.data_type = LOGICAL;
      break;

    case DBF_DATE:
      dbf->record_length += field->size = 8;
      strcpy(field->format, "%8s");
      field->metadata.data_type = DATE;
      break;

    case DBF_GENERAL:
    case DBF_MEMO:
    case DBF_PICTURE:
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

RECORD *dbf_read_next(DBF *dbf)
{
  RECORD *record = NULL;
  CELL *cell = NULL;
  DBF_FIELD *field;
  ssize_t count;
  char *buf, *cur, *tmp;
  int i;
  uint32 len = dbf->record_length;

  DBUG_ENTER("dbf_read_next");

  buf = cur = memset(dbf->record_buffer, 0, dbf->record_length+1);

  if((count=read(dbf->fd, buf, dbf->record_length+1)) < dbf->record_length+1)
  {
    if(count == 1 && buf[0] == DBF_EOF)
    {
      goto endoffile;
    }
    fprintf(stderr, "DBF: Error reading record: read only %i bytes, expected %i bytes\n", count, dbf->record_length+1);
    close(dbf->fd);
    DBUG_RETURN(NULL);
  }

  if(!(record = record_init(dbf)))
    DBUG_RETURN(NULL);

  /* status = cur[0] */
  cur++;

  for(field=dbf->fields, i=0; i<dbf->numfields; field++, i++)
  {
    cell = cell_init(field, &field->metadata);
    switch(field->type)
    {
    case DBF_CHARACTER:
      if(!(cell->data.character = (char *)strndup(cur, field->size)))
        goto oom;
      mygis_trim(cell->data.character, field->size);
      break;

    case DBF_DATE:
      if(!(cell->data.date = (char *)strndup(cur, field->size)))
        goto oom;
      break;

    case DBF_NUMBER:
      /* if field->decimals > 0, fall through to FLOATING */
      if(field->decimals == 0)
      {
        if(!(tmp = (char *)strndup(cur, field->size)))
          goto oom;
        cell->data.number = atoll(tmp);
        free(tmp);
        break;
      }

    case DBF_FLOATING:
      if(!(tmp = (char *)strndup(cur, field->size)))
        goto oom;
      cell->data.floating = atof(tmp);
      free(tmp);
      break;

    case DBF_LOGICAL:
      cell->data.logical = cur[0];
      break;

    case DBF_GENERAL:
    case DBF_MEMO:
    case DBF_PICTURE:
      fprintf(stderr, "Unsupported field type %c!  Please ask for support from the author!\n", field->type);
      return NULL;
    default:
      fprintf(stderr, "Unknown field type %c!\n", field->type);
      return NULL;
    }
    record_append(record, cell);
    cur += field->size;
  }

 endoffile:
  dbf->position++;
  DBUG_RETURN(record);

 oom:
  fprintf(stderr, "DBF: Out of memory!\n");
  DBUG_RETURN(NULL);
}
