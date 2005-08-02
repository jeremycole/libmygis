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

#ifndef SHX_H
#define SHX_H

#include "mygis.h"
#include "sh_header.h"

#define SHX_POS_HEADER             0
#define SHX_POS_DATA             100

#define SHX_LEN_FILE_HEADER      100
#define SHX_LEN_RECORD             8

#define SHX_REC_OFFSET(x)          MYGIS_READ_UINT32_BE((x)+0)
#define SHX_REC_LENGTH(x)          MYGIS_READ_UINT32_BE((x)+4)

#define SHX_INIT                   MYGIS_MALLOC(SHX)
#define SHX_RECORD_INIT            MYGIS_MALLOC(SHX_RECORD)

typedef struct shx_st {
  SH_HEADER         *header;
  int               fd;
  char              *filename;
  char              mode;
  int               flags;
  int               position;
  int               records;
} SHX;

typedef struct shx_record_st {
  uint32            offset;
  uint32            length;
} SHX_RECORD;

/*

PUBLIC API

*/

SHX                 *shx_init(int flags);
int                 shx_open(SHX *shx, char *shxfile, char mode);
SHX_RECORD          *shx_read_next(SHX *shx);
void                shx_seek(SHX *shx, int pos);
void                shx_record_seek(SHX *shx, uint32 record);
void                shx_rewind(SHX *shx);
void                shx_dump(SHX *shx);
void                shx_record_dump(SHX_RECORD *record, int level);
void                shx_record_free(SHX_RECORD *record);
void                shx_close(SHX *shx);
void                shx_free(SHX *shx);

#endif /* SHX_H */
