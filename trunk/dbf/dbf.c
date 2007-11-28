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

#include "dbf_priv.h"

DBF *dbf_init(int flags) {
  DBF *dbf;

  DBUG_ENTER("dbf_init");

  if(!(dbf = DBF_INIT)) {
    DBUG_RETURN(NULL);
  }

  if(!(dbf->header = malloc(DBF_LEN_FILE_HEADER))) {
    free(dbf);
    DBUG_RETURN(NULL);
  }

  dbf->flags = 0;
  dbf->position = -1;
  dbf->record_buffer = NULL;

  DBUG_RETURN(dbf);
}

int dbf_open(DBF *dbf, char *dbffile, char mode)
{
  DBUG_ENTER("dbf_open");
  DBUG_PRINT("info", ("DBF: Opening '%s', mode '%c'", dbffile, mode));

  dbf->mode     = mode;
  dbf->filename = strdup(dbffile);

  if((dbf->fd = open(dbffile, O_RDONLY)) < 0) {
    fprintf(stderr, "Error opening DBF file: %i: %s\n",
	    errno, strerror(errno));
    DBUG_RETURN(-1);
  }

  if(_dbf_read_header(dbf) != 0) {
    DBUG_RETURN(-2);
  }

  dbf_rewind(dbf);

  DBUG_RETURN(dbf->fd);
}

void dbf_seek(DBF *dbf, int pos)
{
  DBUG_ENTER("dbf_seek");
  DBUG_PRINT("info", ("DBF: Seeking to offset %i", pos));
  lseek(dbf->fd, pos, SEEK_SET);
  DBUG_VOID_RETURN;
}

void dbf_seek_record(DBF *dbf, uint32 record)
{
  DBUG_ENTER("dbf_seek_record");
  DBUG_PRINT("info", ("DBF: Record seeking to record %i", record));
  dbf_seek(dbf, DBF_POS_DATA(dbf->header)+(DBF_HDR_LENRECORD(dbf->header)*record));
  dbf->position = record;
  DBUG_VOID_RETURN;
}

void dbf_rewind(DBF *dbf)
{
  DBUG_ENTER("dbf_rewind");
  dbf_seek_record(dbf, 0);
  DBUG_VOID_RETURN;
}

void dbf_dump(DBF *dbf)
{
  DBF_FIELD *field;
  int i;

  DBUG_ENTER("dbf_dump");

  printf("\n");
  printf("DBF: Dump: 0x%08x\n", (int)dbf);
  printf("  Structure:\n");
  printf("    header:         0x%08x\n", (int)dbf->header);
  printf("    filename:       %s\n", dbf->filename);
  printf("    version:        0x%02x\n", dbf->version);
  printf("    numfields:      %i\n", dbf->numfields);
  printf("    fields:         0x%08x\n", (int)dbf->fields);
  printf("    records:        %i\n", dbf->numrecords);
  printf("    record_length:  %i\n", dbf->record_length);
  printf("    fd:             %i\n", dbf->fd);
  printf("    flags:          %i\n", dbf->flags);
  printf("    mode:           %c\n", dbf->mode);
  printf("    position:       %i\n", dbf->position);
  printf("  Fields:\n");
  for(field = dbf->fields, i=0; i<dbf->numfields; field++, i++) {
    printf("    Field %3i:  Name %-10s  Type %c  Length %3i  Decimals %2i  Format %s\n",
	   i, field->name, field->type, field->length, field->decimals,
	   field->format);
  }
  printf("\n\n");

  DBUG_VOID_RETURN;
}

void dbf_close(DBF *dbf)
{
  DBUG_ENTER("dbf_close");
  if(dbf->fd) {
    close(dbf->fd);
  }
  DBUG_VOID_RETURN;
}

void dbf_free(DBF *dbf)
{
  DBUG_ENTER("dbf_free");
  if(dbf) {
    if(dbf->header)   free(dbf->header);
    if(dbf->fields)   free(dbf->fields);
    if(dbf->filename) free(dbf->filename);
    if(dbf->record_buffer) free(dbf->record_buffer);
    free(dbf);
  }
  DBUG_VOID_RETURN;
}
