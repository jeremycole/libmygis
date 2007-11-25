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

#ifndef WKB_PRIV_H
#define WKB_PRIV_H

#include "wkb.h"

POINT      *_wkb_read_points(char *pos, uint32 num, char **next);
LINEARRING *_wkb_read_linearrings(char *pos, uint32 num, char **next);

/* Simple Types, capable of reading multiples */
GEOMETRY_POINT           *_wkb_read_geometry_points(WKB *wkb, uint32 num);
GEOMETRY_LINESTRING      *_wkb_read_geometry_linestrings(WKB *wkb, uint32 num);
GEOMETRY_POLYGON         *_wkb_read_geometry_polygons(WKB *wkb, uint32 num);

/* Complex Types */
GEOMETRY_MULTIPOINT      *_wkb_read_geometry_multipoint(WKB *wkb);
GEOMETRY_MULTILINESTRING *_wkb_read_geometry_multilinestring(WKB *wkb);
GEOMETRY_MULTIPOLYGON    *_wkb_read_geometry_multipolygon(WKB *wkb);


#endif /* WKB_PRIV_H */
