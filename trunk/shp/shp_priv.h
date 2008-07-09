/*
    Copyright (c) 2004-2008, Jeremy Cole and others

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

#ifndef SHP_PRIV_H
#define SHP_PRIV_H

#include "mygis_priv.h"
#include "shp.h"
#include "geometry_priv.h"
#include "sh_header_priv.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SHP_SZ_POINT               (SZ_DOUBLE*2)

#define SHP_NULL                   0
#define SHP_POINT                  1
#define SHP_POLYLINE               3
#define SHP_POLYGON                5
#define SHP_MULTIPOINT             8
#define SHP_POINTZ                11
#define SHP_POLYLINEZ             13
#define SHP_POLYGONZ              15
#define SHP_MULTIPOINTZ           18
#define SHP_POINTM                21
#define SHP_POLYLINEM             23
#define SHP_POLYGONM              25
#define SHP_MULTIPOINTM           28
#define SHP_MULTIPATCH            31

#define SHP_TYPE_MAX 32
extern const char SHP_TYPES[32][20];

#define SHP_POS_HEADER             0
#define SHP_POS_DATA             100

#define SHP_LEN_FILE_HEADER      100
#define SHP_LEN_RECORD_HEADER      8

#define SHP_NO_DATA           -10E38

#define SHP_X(x)                   ((x))
#define SHP_Y(x)                   ((x)+SZ_DOUBLE)

#define SHP_REC1_MBR(x)            ((double *)((x)+0))
#define SHP_REC1_NUMPOINTS(x)      MYGIS_READ_UINT32_LE((x)+32)
#define SHP_REC1_POINTS(x)         ((x)+36)

#define SHP_REC2_MBR(x)            ((double *)((x)+0))
#define SHP_REC2_NUMPARTS(x)       MYGIS_READ_UINT32_LE((x)+32)
#define SHP_REC2_NUMPOINTS(x)      MYGIS_READ_UINT32_LE((x)+36)
#define SHP_REC2_PARTS(x)          ((uint32 *)((x)+40))
#define SHP_REC2_POINTS(x)         ((char *)((x)+40+(SZ_UINT32*SHP_REC2_NUMPARTS(x))))

#define SHP_INIT                   MYGIS_MALLOC(SHP)

int                 _shp_read_header(SHP *shp);
int                 _shp_write_header(SHP *shp);
void                _shp_update_header(SHP *shp);

POINT               *_shp_read_points(char *content, uint32 num);
LINEARRING          *_shp_read_linearring(char *content, uint32 size);

GEOMETRY            *_shp_geometry_null();
GEOMETRY            *_shp_read_geometry_point(char *content);
GEOMETRY            *_shp_read_geometry_multipoint(char *content);
GEOMETRY            *_shp_read_geometry_polyline(char *content);
GEOMETRY            *_shp_read_geometry_polygon(char *content);

#endif /* SHP_PRIV_H */
