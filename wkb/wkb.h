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

#ifndef WKB_H
#define WKB_H

#include "mygis.h"
#include "geometry.h"

#define WKB_SZ_BYTEORDER           1
#define WKB_SZ_TYPE                4
#define WKB_SZ_NUMITEMS            4
#define WKB_SZ_POINT               (SZ_DOUBLE*2)

#define WKB_F_DUPE                 0x0001

#define WKB_UNKNOWN                0
#define WKB_POINT                  1
#define WKB_LINESTRING             2
#define WKB_POLYGON                3
#define WKB_MULTIPOINT             4
#define WKB_MULTILINESTRING        5
#define WKB_MULTIPOLYGON           6
#define WKB_GEOMETRYCOLLECTION     7

#define WKB_BYTEORDER(pos)         MYGIS_READ_BYTE_LE(pos)
#define WKB_TYPE(pos)              MYGIS_READ_UINT32_LE(pos+1)
#define WKB_NUMITEMS(pos)          MYGIS_READ_UINT32_LE(pos+5)
#define WKB_DATA(pos)              (pos+(WKB_TYPE(pos)==WKB_POINT?5:9))

#define WKB_X(pos)                 (pos)
#define WKB_Y(pos)                 (pos+SZ_DOUBLE)

#define WKB_INIT                   MYGIS_MALLOC(WKB)

#define WKB_TYPE_MAX 8
extern const char WKB_TYPES[8][20];

typedef struct wkb_st {
  char       *mydata;
  unsigned int mydata_len;
  char       *data;
  unsigned int data_len;
  char       *cur;
  char       *next;

  int        flags;
} WKB;


/*

THE PUBLIC API

*/

WKB       *wkb_init(int flags);
int       wkb_load(WKB *wkb, char *data, unsigned int data_len, int flags);
GEOMETRY  *wkb_read_next(WKB *wkb);
void      wkb_rewind(WKB *wkb);
void      wkb_free(WKB *wkb);

uint32    wkb_size(GEOMETRY *geometry);
char      *wkb_write(GEOMETRY *geometry, char *wkb);

#endif /* WKB_H */
