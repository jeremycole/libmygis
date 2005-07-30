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

#ifndef SHP_PRIV_H
#define SHP_PRIV_H

#include "shp.h"

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
