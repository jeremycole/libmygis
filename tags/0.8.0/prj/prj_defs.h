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

#ifndef PRJ_DEFS_H
#define PRJ_DEFS_H

typedef struct prj_proj4_names_st
{
  char *prj_name;
  char *proj4_name;
} PRJ_PROJ4_NAMES;

extern PRJ_PROJ4_NAMES prj_proj4_geogcs_names[];
extern PRJ_PROJ4_NAMES prj_proj4_datum_names[];
extern PRJ_PROJ4_NAMES prj_proj4_spheroid_names[];
extern PRJ_PROJ4_NAMES prj_proj4_projection_names[];
extern PRJ_PROJ4_NAMES prj_proj4_unit_names[];
extern PRJ_PROJ4_NAMES prj_proj4_parameter_names[];

char *prj_proj4_names_find(PRJ_PROJ4_NAMES *names, char *name);

#endif /* PRJ_DEFS_H */
