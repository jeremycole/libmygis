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

#ifndef MYGIS_H
#define MYGIS_H

#ifndef DEBUG
#define DBUG_OFF
#endif

#include <mygis/dbug.h>

extern const char *mygis_version;
extern const char *mygis_copyright;
extern const char *mygis_license;

typedef unsigned char      byte;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef signed char        sint8;
typedef signed short       sint16;
typedef signed int         sint32;
typedef signed long long   sint64;

typedef struct point_st {
  double x;
  double y;
/*
  double z;
  double m;
*/
} POINT;

typedef enum linearring_type_en {
  LR_UNKNOWN           = 0,
  LR_EXTERIOR          = 1,
  LR_INTERIOR          = 2
} LINEARRING_TYPE;

typedef struct linearring_st {
  uint32 items;
  POINT *points;
  LINEARRING_TYPE type;
  double area;
} LINEARRING;

#endif /* MYGIS_H */
