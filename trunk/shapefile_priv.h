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

#ifndef SHAPEFILE_PRIV_H
#define SHAPEFILE_PRIV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mygis_priv.h"
#include "shapefile.h"
#include "geometry.h"

#define SHAPEFILE_INIT                  MYGIS_MALLOC(SHAPEFILE)
#define SHAPEFILE_SCAN_INIT             MYGIS_MALLOC(SHAPEFILE_SCAN)
#define SHAPEFILE_RECORD_INIT           MYGIS_MALLOC(SHAPEFILE_RECORD)

#endif /* SHAPEFILE_PRIV_H */
