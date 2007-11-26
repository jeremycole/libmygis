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

#ifndef RECORD_PRIV_H
#define RECORD_PRIV_H

#include "mygis_priv.h"
#include "record.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define RECORD_INIT                    MYGIS_MALLOC(RECORD)
#define CELL_INIT                      MYGIS_MALLOC(CELL)
#define CELL_NODE_INIT                 MYGIS_MALLOC(CELL_NODE)

#endif /* RECORD_PRIV_H */