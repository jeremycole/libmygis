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

char *dbf_record_field(RECORD *record, char *key)
{
  DBF_FIELD *field;
  CELL *cell = NULL;
  CELL_NODE *cell_node = record->head;

  for(; cell_node; cell_node = cell_node->next)
  {
    cell = cell_node->cell;
    field = (DBF_FIELD *) cell->field;

    if(strcasecmp(field->name, key) == 0)
      return cell->data.character;
  }
  return NULL;
}
