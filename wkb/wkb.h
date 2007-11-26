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

#include <mygis/geometry.h>

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
