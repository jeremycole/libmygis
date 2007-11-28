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

#ifndef SHAPEFILE_H
#define SHAPEFILE_H

#include <mygis/shp/shp.h>
#include <mygis/shp/shx.h>
#include <mygis/dbf/dbf.h>
#include <mygis/prj/prj.h>
#include <mygis/compare.h>
#include <mygis/projection.h>

#define SHAPEFILE_NO_SHP                0x0001
#define SHAPEFILE_NO_SHX                0x0002
#define SHAPEFILE_NO_DBF                0x0004
#define SHAPEFILE_NO_PRJ                0x0008

#define SHAPEFILE_HAS_SHP               0x1000
#define SHAPEFILE_HAS_SHX               0x2000
#define SHAPEFILE_HAS_DBF               0x4000
#define SHAPEFILE_HAS_PRJ               0x8000

typedef struct shapefile_st {
  SHP             *shp;
  SHX             *shx;
  DBF             *dbf;
  PRJ             *prj;
  PROJECTION      *projection;
  char            *basename;
  int             flags;
  char            mode;
} SHAPEFILE;

typedef struct shapefile_record_st {
  SHAPEFILE       *shapefile;
  GEOMETRY        *geometry;
  RECORD          *dbf_record;
} SHAPEFILE_RECORD;

typedef struct shapefile_scan_st {
  SHAPEFILE       *shapefile;
  COMPARE         *compare;
  DBF_SCAN        *dbf_scan;
} SHAPEFILE_SCAN;


/*

PUBLIC API

*/

SHAPEFILE           *shapefile_init(int flags);
int                 shapefile_open(SHAPEFILE *shapefile, char *basename, char mode);
void                shapefile_set_projection(SHAPEFILE *shapefile,
                                             PROJECTION *projection);
void                shapefile_seek(SHAPEFILE *shapefile, uint32 record);
SHAPEFILE_RECORD    *shapefile_read_next(SHAPEFILE *shapefile);
void                shapefile_dump(SHAPEFILE *shapefile);
void                shapefile_close(SHAPEFILE *shapefile);
void                shapefile_free(SHAPEFILE *shapefile);

void                shapefile_record_dump(SHAPEFILE_RECORD *record);
void                shapefile_record_free(SHAPEFILE_RECORD *record);

SHAPEFILE_SCAN      *shapefile_scan_init(SHAPEFILE *shapefile,
					 COMPARE *compare,
					 char *key, char *value);
SHAPEFILE_RECORD    *shapefile_scan_read_next(SHAPEFILE_SCAN *scan);
void                shapefile_scan_free(SHAPEFILE_SCAN *scan);

#endif /* SHAPEFILE_H */
