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

#ifndef PRJ_H
#define PRJ_H

#include "mygis.h"
#include "../pairlist.h"
#include "../projection.h"

#define PRJ_INIT                   MYGIS_MALLOC(PRJ)

#define PRJ_NAME_LEN 100

typedef struct prj_kv_st {
  char name[PRJ_NAME_LEN];
  double value;
} PRJ_KV;

typedef struct prj_spheroid_st {
  char name[PRJ_NAME_LEN];
  double value1;
  double value2;
} PRJ_SPHEROID;

typedef struct prj_datum_st {
  char name[PRJ_NAME_LEN];
  PRJ_SPHEROID spheroid;
} PRJ_DATUM;

typedef struct prj_geogcs_st {
  char name[PRJ_NAME_LEN];
  PRJ_DATUM datum;
  PRJ_KV primem;
  PRJ_KV unit;
} PRJ_GEOGCS;

typedef struct prj_projcs_st {
  int is_filled;
  char name[PRJ_NAME_LEN];
  PRJ_GEOGCS geogcs;
  char projection[PRJ_NAME_LEN];
  PRJ_KV unit;
  PAIRLIST *parameters;
} PRJ_PROJCS;

typedef struct prj_st {
  char *filename;
  char *definition;
  char proj4_def[4096];
  PRJ_PROJCS projcs;
} PRJ;

PRJ                 *prj_init(int flags);
int                 prj_parse(PRJ *prj, char *prjfile);
void                prj_dump(PRJ *prj);
void                prj_free(PRJ *prj);

#endif /* PRJ_H */
