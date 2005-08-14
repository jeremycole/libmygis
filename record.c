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
#include "record.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

RECORD *record_init(void *source)
{
  RECORD *record = NULL;
  DBUG_ENTER("record_init");

  if(!(record = RECORD_INIT))
    DBUG_RETURN(NULL);

  record->source = source;

  DBUG_RETURN(record);
}

CELL_NODE *record_append(RECORD *record, CELL *cell)
{
  CELL_NODE *node = NULL;
  DBUG_ENTER("record_append");

  if(!record || !cell)
    DBUG_RETURN(NULL);

  if(!(node = CELL_NODE_INIT))
    DBUG_RETURN(NULL);

  node->cell = cell;
  MYGIS_APPEND_NODE(record, node);
  record->cells++;

  DBUG_RETURN(node);
}

CELL *record_remove(RECORD *record, CELL_NODE *node)
{
  CELL *cell = NULL;
  DBUG_ENTER("record_remove");

  if(!record || !node)
    DBUG_RETURN(NULL);

  cell = node->cell;
  MYGIS_REMOVE_NODE(record, node);
  record->cells--;
  free(node);

  DBUG_RETURN(cell);
}

void record_dump(RECORD *record)
{
  CELL *cell = NULL;
  CELL_NODE *cell_node = record->head;

  DBUG_ENTER("record_dump");

  printf("RECORD: Dump: 0x%08x\n", record);
  for(; cell_node; cell_node = cell_node->next) {
    cell = cell_node->cell;
    
    printf("  %16s: ", cell->metadata->name);
    switch(cell->metadata->data_type) {
    case CHARACTER:
      if(cell->is_null)
        printf("(null)");
      else
        printf(cell->metadata->format, cell->data.character);
      break;
    case NUMBER:
      printf(cell->metadata->format, cell->data.number);
      break;
    case FLOATING:
      printf(cell->metadata->format, cell->data.floating);
      break;
    default:
      printf("(unknown)");
    }
    printf("\n");
  }
  printf("\n");
  DBUG_VOID_RETURN;
}

void record_free(RECORD *record)
{
  DBUG_ENTER("fixed_record_free");
  CELL_NODE *node = NULL;

  if(!record) DBUG_VOID_RETURN;
  while((node=record->head))
    free(record_remove(record, node));
  free(record);
  DBUG_VOID_RETURN;
}
