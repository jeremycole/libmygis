/*
    Copyright (c) 2004, Jeremy Cole

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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "mygis.h"

#define POINT_INIT(x)                  MYGIS_MALLOC_X(POINT, x)
#define LINEARRING_INIT(x)             MYGIS_MALLOC_X(LINEARRING, x)

#define GEOMETRY_INIT                  MYGIS_MALLOC(GEOMETRY)
#define GEOMETRY_POINT_INIT            MYGIS_MALLOC(GEOMETRY_POINT)
#define GEOMETRY_LINESTRING_INIT       MYGIS_MALLOC(GEOMETRY_LINESTRING)
#define GEOMETRY_POLYGON_INIT          MYGIS_MALLOC(GEOMETRY_POLYGON)
#define GEOMETRY_MULTIPOINT_INIT       MYGIS_MALLOC(GEOMETRY_MULTIPOINT)
#define GEOMETRY_MULTILINESTRING_INIT  MYGIS_MALLOC(GEOMETRY_MULTILINESTRING)
#define GEOMETRY_MULTIPOLYGON_INIT     MYGIS_MALLOC(GEOMETRY_MULTIPOLYGON)
#define GEOMETRYCOLLECTION_INIT        MYGIS_MALLOC(GEOMETRYCOLLECTION)

#define GEOMETRY_TYPE_MAX 8

typedef enum geometry_type_en {
  T_NULL               = 0,
  T_POINT              = 1,
  T_LINESTRING         = 2,
  T_POLYGON            = 3,
  T_MULTIPOINT         = 4,
  T_MULTILINESTRING    = 5,
  T_MULTIPOLYGON       = 6,
  T_GEOMETRYCOLLECTION = 7
} GEOMETRY_TYPE;

typedef enum linearring_type_en {
  LR_NONE              = 0,
  LR_ADD               = 1,
  LR_SUBTRACT          = 2
} LINEARRING_TYPE;

extern const char GEOMETRY_TYPES[GEOMETRY_TYPE_MAX][20];

/* Internally-used structures */

typedef struct point_st {
  double x;
  double y;
/*
  double z;
  double m;
*/
} POINT;

typedef struct linearring_st {
  uint32 items;
  POINT *points;
  LINEARRING_TYPE type;
  double area;
} LINEARRING;


/* Externally-used structures */

typedef struct geometry_point_st {
  byte    byteorder;
  POINT   *point;
} GEOMETRY_POINT;

typedef struct geometry_linestring_st {
  byte    byteorder;
  uint32  items;
  POINT   *points;
} GEOMETRY_LINESTRING;

typedef struct geometry_polygon_st {
  byte    byteorder;
  uint32  items;
  LINEARRING   *linearrings;
} GEOMETRY_POLYGON;

typedef struct geometry_multipoint_st {
  byte    byteorder;
  uint32  items;
  POINT   *points;
} GEOMETRY_MULTIPOINT;

typedef struct geometry_multilinestring_st {
  byte    byteorder;
  uint32  items;
  GEOMETRY_LINESTRING *linestrings;
} GEOMETRY_MULTILINESTRING;
  
typedef struct geometry_multipolygon_st {
  byte    byteorder;
  uint32  items;
  GEOMETRY_POLYGON *polygons;
} GEOMETRY_MULTIPOLYGON;
  



typedef union geometry_any {
  GEOMETRY_POINT            *point;
  GEOMETRY_LINESTRING       *linestring;
  GEOMETRY_POLYGON          *polygon;
  GEOMETRY_MULTIPOINT       *multipoint;
  GEOMETRY_MULTILINESTRING  *multilinestring;
  GEOMETRY_MULTIPOLYGON     *multipolygon;
/*
  GEOMETRYCOLLECTION        *geometrycollection;
*/
} GEOMETRY_ANY;

typedef struct geometry_info_values_st {
  char *name;
  char *value;
} GEOMETRY_INFO_VALUE;

typedef struct geometry_info_st {
  uint32  items;
  GEOMETRY_INFO_VALUE *values;
} GEOMETRY_INFO;

typedef struct geometry_mbr_st {
  POINT min;
  POINT max;
} GEOMETRY_MBR;

typedef struct geometry_st {
  byte    byteorder;
  uint32  items;

  GEOMETRY_TYPE  type;
  GEOMETRY_ANY   value;
  GEOMETRY_MBR   mbr;
  GEOMETRY_INFO  info;
} GEOMETRY; 
  
typedef struct geometrycollection_st {
  byte    byteorder;
  uint32  items;

  GEOMETRY *geometries;
} GEOMETRYCOLLECTION;

/*

PUBLIC API

*/

GEOMETRY  *geometry_init(GEOMETRY_TYPE type);
void      geometry_dump(GEOMETRY *geometry, int level);
void      geometry_free(GEOMETRY *geometry);

double    geometry_linearring_area(LINEARRING *linearring);

#endif
