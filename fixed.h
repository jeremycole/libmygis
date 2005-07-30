/*
    Copyright (c) 2004, Jeremy Cole

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

#ifndef FIXED_H
#define FIXED_H 

#include "mygis.h"
#include "compare.h"
#include "fixed.h"

#define FIXED_INIT                     MYGIS_MALLOC(FIXED)
#define FIXED_FIELD_INIT               MYGIS_MALLOC(FIXED_FIELD)
#define FIXED_FIELD_NODE_INIT          MYGIS_MALLOC(FIXED_FIELD_NODE)
#define FIXED_RECORD_INIT              MYGIS_MALLOC(FIXED_RECORD)
#define FIXED_CELL_INIT                MYGIS_MALLOC(FIXED_CELL)
#define FIXED_CELL_NODE_INIT           MYGIS_MALLOC(FIXED_CELL_NODE)

#define FIXED_F_CRLF                   0x0001
#define FIXED_F_NULLS                  0x1000

typedef enum fixed_padding_en {
  LEFT             = 'L',
  RIGHT            = 'R'
} FIXED_PADDING;

typedef enum fixed_type_en {
  CHARACTER        = 'C',
  NUMBER           = 'N',
  LOGICAL          = 'L',
  DATE             = 'D',
  FLOATING         = 'F',
  FLOAT1MM         = '1'
} FIXED_TYPE;

typedef enum fixed_nulls_en {
  NOTNULL          = 'N',
  MAYBENULL        = 'Y'
} FIXED_NULLS;

typedef struct fixed_field_st {
  char          *name;
  FIXED_PADDING padding;
  FIXED_TYPE    type;
  FIXED_NULLS   nulls;
  uint          start;
  uint          end;
  uint          length;
} FIXED_FIELD;

typedef struct fixed_field_node_st {
  FIXED_FIELD *field;
  struct fixed_field_node_st *prev, *next;
} FIXED_FIELD_NODE;

typedef struct fixed_st {
  FIXED_FIELD_NODE *head, *tail;
  uint fields;
  uint record_length;
  char *record_buffer;
  int flags;
  int fd;
  char *filename;
  char mode;
  int position;
} FIXED;

typedef struct fixed_scan_st {
  FIXED           *fixed;
  COMPARE         *compare;
  char            *key;
  char            *value;
  int             last;
} FIXED_SCAN;

typedef union fixed_cell_data_un {
  char            *character;
  long int        number;
  char            logical;
  char            *date;
  float           floating;
} FIXED_CELL_DATA;

typedef struct fixed_cell_st {
  FIXED_FIELD     *field;
  FIXED_CELL_DATA data;
  int             is_null;
} FIXED_CELL;

typedef struct fixed_cell_node_st {
  FIXED_CELL      *cell;
  struct fixed_cell_node_st *prev, *next;
} FIXED_CELL_NODE;

typedef struct fixed_record_st {
  FIXED *fixed;
  FIXED_CELL_NODE *head, *tail;
  uint cells;
} FIXED_RECORD;

FIXED_FIELD       *fixed_field_init();
FIXED_FIELD       *fixed_field_new(char *name, FIXED_PADDING padding,
                                   FIXED_TYPE type, FIXED_NULLS nulls,
				   uint32 length);
void              fixed_field_free(FIXED_FIELD *field);


FIXED             *fixed_init(int flags);
int               fixed_open(FIXED *fixed, char *fixedfile, char mode);
void              fixed_dump(FIXED *fixed);
void              fixed_close(FIXED *fixed);
void              fixed_free(FIXED *fixed);

FIXED_FIELD_NODE  *fixed_append(FIXED *fixed, FIXED_FIELD *field);
FIXED_FIELD       *fixed_remove(FIXED *fixed, FIXED_FIELD_NODE *node);

FIXED_RECORD      *fixed_read_next(FIXED *fixed);

FIXED_RECORD      *fixed_record_init(FIXED *fixed);
void              fixed_record_dump(FIXED_RECORD *record);
void              fixed_record_free(FIXED_RECORD *record);

FIXED_RECORD      *fixed_parse(FIXED *fixed, char *line);

FIXED_SCAN        *fixed_scan_init(FIXED *fixed, COMPARE *compare,
                                   char *key, char *value);
int               fixed_scan_next(FIXED_SCAN *scan);
FIXED_RECORD      *fixed_scan_read_next(FIXED_SCAN *scan);
void              fixed_scan_free(FIXED_SCAN *scan);

#endif /* FIXED_H */
