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

#ifndef RECORD_H
#define RECORD_H

#define RECORD_INIT                    MYGIS_MALLOC(RECORD)
#define CELL_INIT                      MYGIS_MALLOC(CELL)
#define CELL_NODE_INIT                 MYGIS_MALLOC(CELL_NODE)

typedef enum data_type_en {
  CHARACTER,
  NUMBER,
  LOGICAL,
  DATE,
  FLOATING
} DATA_TYPE;

typedef struct metadata_st {
  char            *name;
  char            *format;
  DATA_TYPE       data_type;
} METADATA;

typedef union cell_data_un {
  char            *character;
  long long       number;
  char            logical;
  char            *date;
  double          floating;
} CELL_DATA;

typedef struct cell_st {
  void            *field;
  METADATA        *metadata;
  CELL_DATA       data;
  int             is_null;
} CELL;

typedef struct cell_node_st {
  CELL *cell;
  struct cell_node_st *prev, *next;
} CELL_NODE;

typedef struct record_st {
  void *source;
  CELL_NODE *head, *tail;
  uint cells;
} RECORD;

RECORD     *record_init(void *source);
CELL_NODE  *record_append(RECORD *record, CELL *cell);
CELL       *record_remove(RECORD *record, CELL_NODE *node);
void       record_dump(RECORD *record);
void       record_free(RECORD *record);

CELL  *cell_init(void *field, METADATA *metadata);
void  cell_free(CELL *cell);

#endif /* RECORD_H */
