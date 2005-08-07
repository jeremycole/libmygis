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

  fixed->flags = flags;
  fixed->head = NULL;
  fixed->tail = NULL;
  fixed->fields = 0;
  fixed->record_length = 0;
  fixed->record_buffer = NULL;
  fixed->filename = NULL;

  DBUG_RETURN(fixed);
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
    if(field->type != DISCARD) {
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
  uint cur=0;

  DBUG_ENTER("fixed_recalculate");

  if(!fixed) DBUG_VOID_RETURN;

  node = fixed->head;

  for(; node; node = node->next) {
    node->field->start = cur;
    node->field->end = cur+node->field->length-1;
    cur += node->field->length;
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
  fixed->record_length += field->length;

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
  fixed->record_length -= field->length;
  free(node);

  fixed_recalculate(fixed);

  DBUG_RETURN(field);
}

FIXED_RECORD *fixed_record_init(FIXED *fixed)
{
  FIXED_RECORD *record = NULL;
  DBUG_ENTER("fixed_record_init");

  if(!(record = FIXED_RECORD_INIT))
    DBUG_RETURN(NULL);

  record->fixed = fixed;

  DBUG_RETURN(record);
}

FIXED_CELL_NODE *fixed_record_append(FIXED_RECORD *record, FIXED_CELL *cell)
{
  FIXED_CELL_NODE *node = NULL;
  DBUG_ENTER("fixed_record_append");

  if(!record || !cell)
    DBUG_RETURN(NULL);

  if(!(node = FIXED_CELL_NODE_INIT))
    DBUG_RETURN(NULL);

  node->cell = cell;
  MYGIS_APPEND_NODE(record, node);
  record->cells++;

  DBUG_RETURN(node);
}

FIXED_CELL *fixed_record_remove(FIXED_RECORD *record, FIXED_CELL_NODE *node)
{
  FIXED_CELL *cell = NULL;
  DBUG_ENTER("fixed_record_remove");

  if(!record || !node)
    DBUG_RETURN(NULL);

  cell = node->cell;
  MYGIS_REMOVE_NODE(record, node);
  record->cells--;
  free(node);

  DBUG_RETURN(cell);
}

void fixed_record_dump(FIXED_RECORD *record)
{
  FIXED_CELL *cell = NULL;
  FIXED_CELL_NODE *cell_node = record->head;

  DBUG_ENTER("fixed_record_dump");

  printf("FIXED_RECORD: Dump: 0x%08x\n", record);
  for(; cell_node; cell_node = cell_node->next) {
    cell = cell_node->cell;
    printf("  %16s: ", cell->field->name);
    switch(cell->field->type) {
    case CHARACTER:
      if(cell->is_null)
        printf("(null)");
      else
        printf("%s", cell->data.character);
      break;
    case NUMBER:
      printf("%f", cell->data.number);
      break;
    case FLOAT1MM:
    case FLOATING:
      printf("%f", cell->data.floating);
      break;
    case DISCARD:
      printf("(value discarded)");
      break;
    default:
      printf("(unknown)");
    }
    printf("\n");
  }
  printf("\n");
  DBUG_VOID_RETURN;
}

void fixed_record_free(FIXED_RECORD *record)
{
  DBUG_ENTER("fixed_record_free");
  FIXED_CELL_NODE *node = NULL;

  if(!record) DBUG_VOID_RETURN;
  while((node=record->head))
    free(fixed_record_remove(record, node));
  free(record);
  DBUG_VOID_RETURN;
}

FIXED_RECORD *fixed_parse(FIXED *fixed, char *line)
{
  FIXED_RECORD *record = NULL;
  FIXED_FIELD *field = NULL;
  FIXED_FIELD_NODE *node = NULL;
  FIXED_CELL *cell = NULL;
  char *cur, *tmp;
  int len;

  DBUG_ENTER("fixed_parse");

  if(!fixed || !line)
    DBUG_RETURN(NULL);

  if(!(record = fixed_record_init(fixed)))
    DBUG_RETURN(NULL);

  for(node=fixed->head; node; node = node->next) {
    field=node->field; cur=line+field->start;

    if(!(cell = FIXED_CELL_INIT))
      goto oom;
      
    cell->field   = field;
    cell->is_null = 0;

    switch(field->type) {
    case CHARACTER:
      for(len=field->length; *cur && *cur == ' ' && len > 0; cur++, len--);
      if(!(cell->data.character = strndup(cur, len)))
        goto oom;
      mygis_trim(cell->data.character, len);
      if(field->nulls == MAYBENULL && fixed->flags & FIXED_F_NULLS && strlen(cell->data.character)==0) {
        cell->is_null = 1;
      }
      break;
    case NUMBER:
      if(!(tmp = (char *)strndup(cur, field->length)))
        goto oom;
      cell->data.number = atof(tmp);
      free(tmp);
      break;
    case FLOAT1MM:
    case FLOATING:
      if(!(tmp = (char *)strndup(cur, field->length)))
        goto oom;
      cell->data.floating = (float) atof(tmp);
      free(tmp);
      if(field->type == FLOAT1MM)
        cell->data.floating /= 1000000;
      break;
    case LOGICAL:
      cell->data.logical = cur[0];
      break;
    case DISCARD:
      /* discard values */
      break;
    }
    fixed_record_append(record, cell);
  }  

  DBUG_RETURN(record);

 oom:
  fprintf(stderr, "FIXED: Out of memory!");
  DBUG_RETURN(NULL);
}


FIXED_RECORD *fixed_read_next(FIXED *fixed)
{
  FIXED_RECORD *record = NULL;
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
    fprintf(stderr, "FIXED: Short read, read only %i bytes, expected %i bytes.",
            count, fixed->record_length);
    close(fixed->fd);
    DBUG_RETURN(NULL);
  }

  if(fixed->flags & FIXED_F_CRLF) {
    read(fixed->fd, tmp, 2);
    if(tmp[0] != '\r' || tmp[1] != '\n') {
      fprintf(stderr, "FIXED: (1) Badly formatted file or bad definition?");
    }
  } else {
    read(fixed->fd, tmp, 1);
    if(tmp[0] == '\r') {
      fixed->flags |= FIXED_F_CRLF;
      read(fixed->fd, tmp, 1); /* throw away \n */
    } else if(!(tmp[0] == '\n' || tmp[0] == 0x1a)) {
      fprintf(stderr, "FIXED: (2) Badly formatted file or bad definition?");
    }
  }

  record = fixed_parse(fixed, fixed->record_buffer);

  DBUG_RETURN(record);
}
