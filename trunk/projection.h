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

#ifndef PROJECTION_H
#define PROJECTION_H

#ifdef HAVE_PROJECTION
#include <proj_api.h>
#endif /* HAVE_PROJECTION */

#include "mygis.h"
#include "pairlist.h"

typedef struct projection_st {
  int is_set;
  char *from_name;
  char *from;
  char *to_name;
  char *to;
#ifdef HAVE_PROJECTION
  projPJ proj4_pj_from;
  projPJ proj4_pj_to;
#endif /* HAVE_PROJECTION */
} PROJECTION;

#define PROJECTION_INIT                      MYGIS_MALLOC(PROJECTION)

PROJECTION *projection_init();
int projection_set(PROJECTION *proj, char *from, char *to);
void projection_unset(PROJECTION *proj);
POINT *projection_transform(PROJECTION *proj, POINT *point);
void projection_dump(PROJECTION *proj);
void projection_free(PROJECTION *proj);

#endif /* PAIRLIST_H */
