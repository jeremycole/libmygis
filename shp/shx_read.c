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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mygis.h"
#include "geometry.h"

#include "shx.h"

int _shx_read_header(SHX *shx)
{
  DBUG_ENTER("_shx_read_header");

  shx_seek(shx, SHX_POS_HEADER);

  if(!(shx->header = _sh_header_read(shx->fd))) {
    close(shx->fd);
    DBUG_RETURN(-2);
  }

  DBUG_RETURN(0);
}

SHX_RECORD *shx_read_next(SHX *shx)
{
  SHX_RECORD *record;
  uint32 count;
  char buf[SHX_LEN_RECORD];

  DBUG_ENTER("shx_read_next");

  if(!shx)
    DBUG_RETURN(NULL);

  if((count=read(shx->fd, buf, SHX_LEN_RECORD)) != SHX_LEN_RECORD) {
    if(count > 0) {
      fprintf(stderr, "Oops!\n");
    }
    DBUG_RETURN(NULL);
  }

  if(!(record = SHX_RECORD_INIT)) {
    DBUG_RETURN(NULL);
  }

  record->offset = 2*SHX_REC_OFFSET(buf);
  record->length = 2*SHX_REC_LENGTH(buf);

  shx->position++;
  DBUG_RETURN(record);
}
