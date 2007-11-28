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

#ifndef SHX_PRIV_H
#define SHX_PRIV_H

#include "mygis_priv.h"
#include "shx.h"
#include "geometry.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SHX_POS_HEADER             0
#define SHX_POS_DATA             100

#define SHX_LEN_FILE_HEADER      100
#define SHX_LEN_RECORD             8

#define SHX_REC_OFFSET(x)          MYGIS_READ_UINT32_BE((x)+0)
#define SHX_REC_LENGTH(x)          MYGIS_READ_UINT32_BE((x)+4)

#define SHX_INIT                   MYGIS_MALLOC(SHX)
#define SHX_RECORD_INIT            MYGIS_MALLOC(SHX_RECORD)

int _shx_read_header(SHX *shx);
int _shx_write_header(SHX *shx);

#endif /* SHX_PRIV_H */
