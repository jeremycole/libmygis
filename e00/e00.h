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

#ifndef E00_H
#define E00_H

#include <stdlib.h>

typedef enum e00_section_id_en {
  UNKNOWN = 0,
  ARC =   1,
  CNT =   2,
  LAB =   3,
  PAL =   4,
  PAR =   5,
  TOL =   6,
  TXT =   7,
  TX6 =   8,
  TX7 =   9,
  IFO =  10,
  RXP =  11,
  RPL =  12,
  LOG =  13,
  PRJ =  14,
  SIN =  15,
} E00_SECTION_ID;

#define E00_SECTION_IDS 16

typedef struct e00_section_tag_st {
  char              *tag;
  E00_SECTION_ID    id;
} E00_SECTION_TAG;

extern E00_SECTION_TAG E00_SECTION_TAGS[];

typedef struct e00_section_st {
  E00_SECTION_ID    id;
  int               fd;
  char              *filename;
  FILE              *file;
  fpos_t            start_pos;
  int               precision;
} E00_SECTION;

typedef struct e00_sections_st {
  E00_SECTION       *arc;
  E00_SECTION       *lab;

  E00_SECTION       *cnt;
  E00_SECTION       *pal;
  E00_SECTION       *par;
  E00_SECTION       *tol;
  E00_SECTION       *txt;
  E00_SECTION       *tx6;
  E00_SECTION       *tx7;
  E00_SECTION       *ifo;
} E00_SECTIONS;

typedef struct e00_st {
  int               fd;
  char              *filename;
  char              mode;
  int               flags;
  int               position;
  int               records;
  E00_SECTIONS      sections;
} E00;


/*

PUBLIC API

*/

E00       *e00_init(int flags);
int       e00_open(E00 *e00, char *e00file, char mode);
void      e00_seek(E00 *e00, int pos);
void      e00_record_seek(E00 *e00, uint32 record);
void      e00_rewind(E00 *e00);
void      e00_dump(E00 *e00);
void      e00_close(E00 *e00);
void      e00_free(E00 *e00);

#endif /* E00_H */
