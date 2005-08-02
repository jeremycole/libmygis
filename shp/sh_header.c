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

#include "mygis.h"
#include "geometry.h"

#include "shp.h"
#include "shp_priv.h"
#include "sh_header.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void _sh_header_swap(SH_HEADER *header)
{
  DBUG_ENTER("_sh_header_swap");
  MYGIS_BE_UINT32(&header->filecode);
  MYGIS_BE_UINT32(&header->unused1);
  MYGIS_BE_UINT32(&header->unused2);
  MYGIS_BE_UINT32(&header->unused3);
  MYGIS_BE_UINT32(&header->unused4);
  MYGIS_BE_UINT32(&header->unused5);
  MYGIS_BE_UINT32(&header->filelength);
  MYGIS_LE_UINT32(&header->version);
  MYGIS_LE_UINT32(&header->shapetype);
  MYGIS_LE_DOUBLE(&header->mbr_minx);
  MYGIS_LE_DOUBLE(&header->mbr_miny);
  MYGIS_LE_DOUBLE(&header->mbr_maxx);
  MYGIS_LE_DOUBLE(&header->mbr_maxy);
  MYGIS_LE_DOUBLE(&header->mbr_minz);
  MYGIS_LE_DOUBLE(&header->mbr_maxz);
  MYGIS_LE_DOUBLE(&header->mbr_minm);
  MYGIS_LE_DOUBLE(&header->mbr_maxm);
  DBUG_VOID_RETURN;
}

SH_HEADER *_sh_header_read(int fd)
{
  SH_HEADER *header;
  ssize_t count;

  DBUG_ENTER("_sh_header_read");

  if(!(header = SH_HEADER_INIT)) {
    DBUG_RETURN(NULL);
  }

  if((count=read(fd, header, sizeof(SH_HEADER))) < sizeof(SH_HEADER)) {
    fprintf(stderr, "SH: Error reading header: read only %i bytes, expected %i bytes\n", count, sizeof(SH_HEADER));
    close(fd);
    DBUG_RETURN(NULL);
  }

  _sh_header_swap(header);

  DBUG_RETURN(header);
}

int _sh_header_write(int fd, SH_HEADER *header)
{
  SH_HEADER *tmp;
  ssize_t count;

  DBUG_ENTER("_sh_header_write");

  if(!(tmp = (SH_HEADER *)malloc(sizeof(SH_HEADER)))) {
    DBUG_RETURN(-1);
  }

  memcpy(tmp, header, sizeof(SH_HEADER));
  _sh_header_swap(tmp);  /* reverse the byte swapping */

  if((count=write(fd, &tmp, sizeof(SH_HEADER))) < sizeof(SH_HEADER)) {
    fprintf(stderr, "SH: Error writing header: wrote only %i bytes, expected %i bytes\n", count, sizeof(SH_HEADER));
    close(fd);
    DBUG_RETURN(-2);
  }
  DBUG_RETURN(0);
}
