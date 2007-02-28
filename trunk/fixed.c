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

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

FIXED_FIELD *fixed_field_init()
{
  FIXED_FIELD *field;

  DBUG_ENTER("fixed_field_init");

  if(!(field = FIXED_FIELD_INIT))
    DBUG_RETURN(NULL);

  DBUG_RETURN(field);
}

FIXED_FIELD *fixed_field_new(char *name, FIXED_PADDING padding,
                             FIXED_TYPE type, FIXED_NULLS nulls,
			     uint32 length)
{
  FIXED_FIELD *field;

  DBUG_ENTER("fixed_field_new");

  if(!(field = fixed_field_init()))
    goto err1;
    
  if(!(field->name = strdup(name)))
    goto err2;

  field->padding = padding;
  field->type    = type;
  field->nulls   = nulls;
  field->length  = length;
  
  field->metadata.name   = field->name;
  field->metadata.format = field->format;
  switch(field->type) {
   case FIXED_CHARACTER:
    strcpy(field->format, "%s");
    field->metadata.data_type = CHARACTER;
    break;
   case FIXED_NUMBER:
    strcpy(field->format, "%lld");
    field->metadata.data_type = NUMBER;
    break;
   case FIXED_LOGICAL:
    strcpy(field->format, "%c");
    field->metadata.data_type = LOGICAL;
    break;
   case FIXED_FLOATING:
   case FIXED_FLOAT1MM:
    strcpy(field->format, "%f");
    field->metadata.data_type = FLOATING;
    break;
   case FIXED_DISCARD:
    break;
  };

  DBUG_RETURN(field);

 err2:
  free(field);
 err1:
  DBUG_RETURN(NULL);
}

void fixed_field_dump(FIXED_FIELD *field)
{
  DBUG_ENTER("fixed_field_dump");

  printf("  FIXED_FIELD: 0x%08x Name '%s', Padding %c, Type %c, Length %d\n"
         "                      Start %d, End %d\n",
         (unsigned int)field, field->name, 
	 field->padding, field->type, field->length,
	 field->start, field->end);

  DBUG_VOID_RETURN;
}

void fixed_field_free(FIXED_FIELD *field)
{
  DBUG_ENTER("fixed_field_free");

  if(!field)
    DBUG_VOID_RETURN;

  free(field->name);
  free(field);
  
  DBUG_VOID_RETURN;
}


FIXED *fixed_init(int flags)
{
  FIXED *fixed;

  DBUG_ENTER("fixed_init");
  if(!(fixed = FIXED_INIT))
    DBUG_RETURN(NULL);

  fixed->flags         = flags;
  fixed->head          = NULL;
  fixed->tail          = NULL;
  fixed->fields        = 0;
  fixed->record_length = 0;
  fixed->record_buffer = NULL;
  fixed->filename      = NULL;
  
  fixed->options.gap   = 0;

  DBUG_RETURN(fixed);
}

FIXED_OPTIONS *fixed_options(FIXED *fixed)
{
  return &fixed->options;
}

int fixed_open(FIXED *fixed, char *fixedfile, char mode)
{
  DBUG_ENTER("fixed_open");
  DBUG_PRINT("info", ("FIXED: Opening '%s', mode '%c'", fixedfile, mode));

  fixed->mode = mode;
  fixed->filename = strdup(fixedfile);

  if((fixed->fd = open(fixedfile, O_RDONLY)) < 0) {
    DBUG_PRINT("error", ("Error opening FIXED file: %i: %s\n",
                         errno, strerror(errno)));
    DBUG_RETURN(-1);
  }
  DBUG_RETURN(fixed->fd);
}

int fixed_file_def(FIXED *fixed, FIXED_FILE_DEF *file_def, uint length)
{
  uint field;
  FIXED_FILE_DEF *field_def;
  
  DBUG_ENTER("fixed_file_def");
  
  for(field=0; field<length; field++) {
    field_def = &file_def[field];
    fixed_append(fixed, 
                 fixed_field_new(field_def->name, field_def->padding,
                   field_def->type, field_def->nulls,
          			   field_def->length));
  }
  DBUG_RETURN(1);
}

void fixed_dump(FIXED *fixed)
{
  FIXED_FIELD_NODE *node = fixed->head;
  FIXED_FIELD *field = NULL;
  uint i;

  DBUG_ENTER("fixed_dump");

  printf("FIXED: Dump: 0x%08x\n", (unsigned int)fixed);
  for(i=0; node; node=node->next, i++) {
    field = node->field;
    printf("  Field %2i: %-10s: ", i, field->name);
    if(field->type != FIXED_DISCARD) {
      printf("Type %c, Pad %c, Nulls %c, ",
	           field->type, field->padding, field->nulls);
    } else {
      printf("(values discarded),     ");
    }
    printf("Len %3d, Start %3d, End %3d\n",
	         field->length, field->start, field->end);
  }
  if(i==0)
    printf("  No fields.\n");

  printf("\n");

  DBUG_VOID_RETURN;
}

void fixed_recalculate(FIXED *fixed)
{
  FIXED_FIELD_NODE *node = NULL;
  FIXED_OPTIONS *options = &fixed->options;
  uint cur=0, gap=0;

  DBUG_ENTER("fixed_recalculate");

  if(!fixed) DBUG_VOID_RETURN;

  node = fixed->head;

  for(; node; node = node->next) {
    node->field->start = cur + (gap=(cur==0?0:options->gap));
    node->field->end   = node->field->start + node->field->length-1;
    cur += gap + node->field->length;
    fixed->record_length = node->field->end+1;
  }

  DBUG_VOID_RETURN;
}

void fixed_close(FIXED *fixed)
{
  DBUG_ENTER("fixed_close");
  if(fixed->fd)
    close(fixed->fd);
  DBUG_VOID_RETURN;
}

void fixed_free(FIXED *fixed)
{
  FIXED_FIELD_NODE *node;
  DBUG_ENTER("fixed_free");
  if(!fixed) DBUG_VOID_RETURN;

  while((node=fixed->head))
    free(fixed_remove(fixed, node));

  free(fixed->record_buffer);
  free(fixed->filename);
  free(fixed);
  DBUG_VOID_RETURN;
}

FIXED_FIELD_NODE *fixed_append(FIXED *fixed, FIXED_FIELD *field)
{
  FIXED_FIELD_NODE *node = NULL;

  DBUG_ENTER("fixed_append");
  DBUG_PRINT("info", ("name=%s", field->name));

  if((!field) || (!field)) DBUG_RETURN(NULL);

  if(!(node = FIXED_FIELD_NODE_INIT))
    DBUG_RETURN(NULL);

  node->prev = node->next = NULL;
  node->field = field;

  MYGIS_APPEND_NODE(fixed, node);
  fixed->fields++;

  fixed_recalculate(fixed);

  DBUG_RETURN(node);
}

FIXED_FIELD *fixed_remove(FIXED *fixed, FIXED_FIELD_NODE *node)
{
  FIXED_FIELD *field = NULL;

  DBUG_ENTER("fixed_remove");

  if((!fixed) || (!node)) DBUG_RETURN(NULL);
  if(fixed->fields == 0) DBUG_RETURN(NULL);

  field = node->field;

  MYGIS_REMOVE_NODE(fixed, node);
  fixed->fields--;
  free(node);

  fixed_recalculate(fixed);

  DBUG_RETURN(field);
}


RECORD *fixed_parse(FIXED *fixed, char *line)
{
  RECORD *record = NULL;
  CELL *cell = NULL;
  FIXED_FIELD *field = NULL;
  FIXED_FIELD_NODE *node = NULL;
  char *cur, *tmp;
  int len;

  DBUG_ENTER("fixed_parse");

  if(!fixed || !line)
    DBUG_RETURN(NULL);

  if(!(record = record_init(fixed)))
    DBUG_RETURN(NULL);

  for(node=fixed->head; node; node = node->next) {
    field=node->field; cur=line+field->start;

    if(!(cell = CELL_INIT))
      goto oom;
    
    cell->metadata = &field->metadata;
    cell->field   = field;
    cell->is_null = 0;

    switch(field->type) {
    case FIXED_CHARACTER:
      for(len=field->length; *cur && *cur == ' ' && len > 0; cur++, len--);
      if(!(cell->data.character = strndup(cur, len)))
        goto oom;
      mygis_trim(cell->data.character, len);
      if(field->nulls == MAYBENULL && fixed->flags & FIXED_F_NULLS && strlen(cell->data.character)==0) {
        cell->is_null = 1;
      }
      break;
    case FIXED_NUMBER:
      if(!(tmp = (char *)strndup(cur, field->length)))
        goto oom;
      DBUG_PRINT("info", ("value = '%s'", tmp));
      cell->data.number = (long long)atoll(tmp);
      free(tmp);
      break;
    case FIXED_FLOAT1MM:
    case FIXED_FLOATING:
      if(!(tmp = (char *)strndup(cur, field->length)))
        goto oom;
      cell->data.floating = (double) atof(tmp);
      free(tmp);
      if(field->type == FIXED_FLOAT1MM)
        cell->data.floating /= 1000000.0;
      break;
    case FIXED_LOGICAL:
      cell->data.logical = cur[0];
      break;
    case FIXED_DISCARD:
      /* discard values */
      break;
    }
    record_append(record, cell);
  }  

  DBUG_RETURN(record);

 oom:
  fprintf(stderr, "FIXED: Out of memory!");
  DBUG_RETURN(NULL);
}


RECORD *fixed_read_next(FIXED *fixed)
{
  RECORD *record = NULL;
  ssize_t rsize, count;
  char tmp[3];
  
  DBUG_ENTER("fixed_read_next");
  if(!fixed) DBUG_RETURN(NULL);
 
  if(!fixed->record_buffer)
    if(!(fixed->record_buffer = (char *)realloc(fixed->record_buffer, fixed->record_length+3)))
      DBUG_RETURN(NULL);

  if((count = read(fixed->fd, fixed->record_buffer, fixed->record_length)) < fixed->record_length) {
    if(count == 0 || (count == 1 && fixed->record_buffer[0] == 0x1a)) 
      DBUG_RETURN(NULL); /* end of file */
    fprintf(stderr, "FIXED: Short read, read only %i bytes, expected %i bytes.\n",
            count, fixed->record_length);
    close(fixed->fd);
    DBUG_RETURN(NULL);
  }

  if(fixed->flags & FIXED_F_CRLF) {
    read(fixed->fd, tmp, 2);
    if(tmp[0] != '\r' || tmp[1] != '\n') {
      fprintf(stderr, "FIXED: (1) Badly formatted file or bad definition?\n");
    }
  } else {
    read(fixed->fd, tmp, 1);
    if(tmp[0] == '\r') {
      fixed->flags |= FIXED_F_CRLF;
      read(fixed->fd, tmp, 1); /* throw away \n */
    } else if(!(tmp[0] == '\n' || tmp[0] == 0x1a)) {
      fprintf(stderr, "FIXED: (2) Badly formatted file or bad definition?  Found '%c' when looking for end of line.\n", tmp[0]);
    }
  }

  record = fixed_parse(fixed, fixed->record_buffer);

  DBUG_RETURN(record);
}
