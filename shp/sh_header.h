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

#ifndef SH_HEADER_H
#define SH_HEADER_H

#include <mygis/mygis.h>

typedef struct sh_header_st {
  uint32            filecode;
  uint32            unused1;
  uint32            unused2;
  uint32            unused3;
  uint32            unused4;
  uint32            unused5;
  uint32            filelength;
  uint32            version;
  uint32            shapetype;
  double            mbr_minx;
  double            mbr_miny;
  double            mbr_maxx;
  double            mbr_maxy;
  double            mbr_minz;
  double            mbr_maxz;
  double            mbr_minm;
  double            mbr_maxm;
} SH_HEADER;

SH_HEADER           *_sh_header_read(int fd);
int                 _sh_header_write(int fd, SH_HEADER *header);
void                _sh_header_swap(SH_HEADER *header);

#endif /* SH_HEADER_H */
