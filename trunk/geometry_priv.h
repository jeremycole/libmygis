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

#ifndef GEOMETRY_PRIV_H
#define GEOMETRY_PRIV_H

#include "mygis_priv.h"
#include "geometry.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "projection_priv.h"

#define GEOMETRY_INIT                  MYGIS_MALLOC(GEOMETRY)
#define GEOMETRY_POINT_INIT            MYGIS_MALLOC(GEOMETRY_POINT)
#define GEOMETRY_LINESTRING_INIT       MYGIS_MALLOC(GEOMETRY_LINESTRING)
#define GEOMETRY_POLYGON_INIT          MYGIS_MALLOC(GEOMETRY_POLYGON)
#define GEOMETRY_MULTIPOINT_INIT       MYGIS_MALLOC(GEOMETRY_MULTIPOINT)
#define GEOMETRY_MULTILINESTRING_INIT  MYGIS_MALLOC(GEOMETRY_MULTILINESTRING)
#define GEOMETRY_MULTIPOLYGON_INIT     MYGIS_MALLOC(GEOMETRY_MULTIPOLYGON)
#define GEOMETRYCOLLECTION_INIT        MYGIS_MALLOC(GEOMETRYCOLLECTION)

#define GEOMETRY_POINT_INIT_X(x)       MYGIS_MALLOC_X(GEOMETRY_POINT, (x))
#define GEOMETRY_LINESTRING_INIT_X(x)  MYGIS_MALLOC_X(GEOMETRY_LINESTRING, (x))
#define GEOMETRY_POLYGON_INIT_X(x)     MYGIS_MALLOC_X(GEOMETRY_POLYGON, (x))


#endif /* GEOMETRY_PRIV_H */