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

#ifndef FIXED_H
#define FIXED_H 

#include "mygis.h"
#include "compare.h"
#include "record.h"
#include "fixed.h"

#define FIXED_INIT                     MYGIS_MALLOC(FIXED)
#define FIXED_FIELD_INIT               MYGIS_MALLOC(FIXED_FIELD)
#define FIXED_FIELD_NODE_INIT          MYGIS_MALLOC(FIXED_FIELD_NODE)

#define FIXED_F_CRLF                   0x0001
#define FIXED_F_NULLS                  0x1000

typedef enum fixed_padding_en {
  LEFT             = 'L',
  RIGHT            = 'R'
} FIXED_PADDING;

typedef enum fixed_type_en {
  FIXED_CHARACTER        = 'C',
  FIXED_NUMBER           = 'N',
  FIXED_LOGICAL          = 'L',
  FIXED_DATE             = 'D',
  FIXED_FLOATING         = 'F',
  FIXED_FLOAT1MM         = '1',
  FIXED_DISCARD          = '*'
} FIXED_TYPE;

typedef enum fixed_nulls_en {
  NOTNULL          = 'N',
  MAYBENULL        = 'Y'
} FIXED_NULLS;

typedef struct fixed_field_st {
  char          *name;
  char          format[10];
  FIXED_PADDING padding;
  FIXED_TYPE    type;
  FIXED_NULLS   nulls;
  uint          start;
  uint          end;
  uint          length;
  METADATA      metadata;
} FIXED_FIELD;

typedef struct fixed_field_node_st {
  FIXED_FIELD *field;
  struct fixed_field_node_st *prev, *next;
} FIXED_FIELD_NODE;

typedef struct fixed_options_st {
  uint          gap;
} FIXED_OPTIONS;

typedef struct fixed_st {
  FIXED_FIELD_NODE *head, *tail;
  FIXED_OPTIONS    options;
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

typedef struct fixed_file_def_st {
  char            *name;
  FIXED_PADDING   padding;
  FIXED_TYPE      type;
  FIXED_NULLS     nulls;
  uint            length;
} FIXED_FILE_DEF;

FIXED_FIELD       *fixed_field_init();
FIXED_FIELD       *fixed_field_new(char *name, FIXED_PADDING padding,
                                   FIXED_TYPE type, FIXED_NULLS nulls,
				                           uint32 length);
void              fixed_field_free(FIXED_FIELD *field);


FIXED             *fixed_init(int flags);
FIXED_OPTIONS     *fixed_options(FIXED *fixed);
int               fixed_file_def(FIXED *fixed, FIXED_FILE_DEF *file_def,
                                 uint length);
int               fixed_open(FIXED *fixed, char *fixedfile, char mode);
void              fixed_dump(FIXED *fixed);
void              fixed_close(FIXED *fixed);
void              fixed_free(FIXED *fixed);

FIXED_FIELD_NODE  *fixed_append(FIXED *fixed, FIXED_FIELD *field);
FIXED_FIELD       *fixed_remove(FIXED *fixed, FIXED_FIELD_NODE *node);

RECORD            *fixed_read_next(FIXED *fixed);

RECORD            *fixed_parse(FIXED *fixed, char *line);

FIXED_SCAN        *fixed_scan_init(FIXED *fixed, COMPARE *compare,
                                   char *key, char *value);
int               fixed_scan_next(FIXED_SCAN *scan);
RECORD            *fixed_scan_read_next(FIXED_SCAN *scan);
void              fixed_scan_free(FIXED_SCAN *scan);

#endif /* FIXED_H */
