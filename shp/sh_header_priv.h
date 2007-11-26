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

#ifndef SH_HEADER_PRIV_H
#define SH_HEADER_PRIV_H

#include "mygis_priv.h"
#include "sh_header.h"

#define SH_HDR_FILECODE(x)         MYGIS_READ_UINT32_BE((x)+0)
#define SH_HDR_UNUSED1(x)          MYGIS_READ_UINT32_BE((x)+4)
#define SH_HDR_UNUSED2(x)          MYGIS_READ_UINT32_BE((x)+8)
#define SH_HDR_UNUSED3(x)          MYGIS_READ_UINT32_BE((x)+12)
#define SH_HDR_UNUSED4(x)          MYGIS_READ_UINT32_BE((x)+16)
#define SH_HDR_UNUSED5(x)          MYGIS_READ_UINT32_BE((x)+20)
#define SH_HDR_FILELENGTH(x)       MYGIS_READ_UINT32_BE((x)+24)
#define SH_HDR_VERSION(x)          MYGIS_READ_UINT32_LE((x)+28)
#define SH_HDR_SHAPETYPE(x)        MYGIS_READ_UINT32_LE((x)+32)
#define SH_HDR_MBR_MINX(x)         MYGIS_READ_DOUBLE_LE((x)+36)
#define SH_HDR_MBR_MINY(x)         MYGIS_READ_DOUBLE_LE((x)+44)
#define SH_HDR_MBR_MAXX(x)         MYGIS_READ_DOUBLE_LE((x)+52)
#define SH_HDR_MBR_MAXY(x)         MYGIS_READ_DOUBLE_LE((x)+60)
#define SH_HDR_MBR_MINZ(x)         MYGIS_READ_DOUBLE_LE((x)+68)
#define SH_HDR_MBR_MAXZ(x)         MYGIS_READ_DOUBLE_LE((x)+76)
#define SH_HDR_MBR_MINM(x)         MYGIS_READ_DOUBLE_LE((x)+84)
#define SH_HDR_MBR_MAXM(x)         MYGIS_READ_DOUBLE_LE((x)+92)

#define SH_HEADER_INIT             MYGIS_MALLOC(SH_HEADER)

#endif /* SH_HEADER_PRIV_H */