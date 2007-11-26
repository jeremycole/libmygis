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

#ifndef FIXED_PRIV_H
#define FIXED_PRIV_H 

#include "fixed.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIXED_INIT                     MYGIS_MALLOC(FIXED)
#define FIXED_FIELD_INIT               MYGIS_MALLOC(FIXED_FIELD)
#define FIXED_FIELD_NODE_INIT          MYGIS_MALLOC(FIXED_FIELD_NODE)

#define FIXED_F_CRLF                   0x0001
#define FIXED_F_NULLS                  0x1000

#endif /* FIXED_PRIV_H */