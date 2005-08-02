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

#ifndef TIGER_H
#define TIGER_H 

#include "compare.h"
#include "fixed.h"
#include "geometry.h"

#define TIGER_INIT                      MYGIS_MALLOC(TIGER)
#define TIGER_RECORD_INIT               MYGIS_MALLOC(TIGER_RECORD)
#define TIGER_SCAN_INIT                 MYGIS_MALLOC(TIGER_SCAN)

#define TIGER_MAX_FILE_TYPE  20

typedef enum tiger_file_type_en {
  RT1, RT2, RT4, RT5, RT6, RT7, RT8,
  RTA, RTB, RTC, RTE, RTH, RTI, RTM,
  RTP, RTR, RTS, RTT, RTU, RTZ
} TIGER_FILE_TYPE;

typedef struct tiger_file_def_st {
  char            *name;
  FIXED_PADDING   padding;
  FIXED_TYPE      type;
  FIXED_NULLS     nulls;
  uint            length;
} TIGER_FILE_DEF;

typedef struct tiger_file_types_st {
  TIGER_FILE_TYPE type;
  char            *record_type;
  char            *name;
  char            *file_ext[5];
  uint            num_fields;
  TIGER_FILE_DEF  *file_def;
} TIGER_FILE_TYPES;

typedef struct tiger_file_st {
  FIXED           *fixed;
  TIGER_FILE_TYPE type;
  char            *filename;
  int             flags;
  char            mode;
} TIGER_FILE;

typedef struct tiger_file_node_st {
  TIGER_FILE      *file;
  struct tiger_file_node_st *prev, *next;
} TIGER_FILE_NODE;

typedef struct tiger_st {
  TIGER_FILE      files[TIGER_MAX_FILE_TYPE]; 
  char            *basename;
  int             flags;
  char            mode;
} TIGER;

typedef struct tiger_record_st {
  TIGER           *tiger;
  TIGER_FILE_TYPE type;
  FIXED_RECORD    *fixed_record;
} TIGER_RECORD;

typedef struct tiger_scan_st {
  TIGER           *tiger;
  COMPARE         *compare;
  FIXED_SCAN      *fixed_scan;
} TIGER_SCAN;


/*

PUBLIC API

*/

extern TIGER_FILE_TYPES tiger_file_types[TIGER_MAX_FILE_TYPE];

TIGER               *tiger_init(int flags);
int                 tiger_open(TIGER *tiger, char *basename, char mode);
void                tiger_dump(TIGER *tiger);
void                tiger_close(TIGER *tiger);
void                tiger_free(TIGER *tiger);

TIGER_RECORD        *tiger_read_next(TIGER *tiger, TIGER_FILE_TYPE type);

TIGER_RECORD        *tiger_record_init(TIGER *tiger, TIGER_FILE_TYPE type);
void                tiger_record_dump(TIGER_RECORD *record);
void                tiger_record_free(TIGER_RECORD *record);

#endif /* TIGER_H */
