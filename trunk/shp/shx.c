/*
    Copyright (c) 2004-2008, Jeremy Cole and others

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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "sh_header.h"
#include "shp.h"
#include "shx.h"
#include "shp_priv.h"
#include "shx_priv.h"


SHX *shx_init(int flags)
{
  SHX *shx;

  DBUG_ENTER("shx_init");

  if(!(shx = SHX_INIT)) return NULL;
  if(!(shx->header = malloc(SHX_LEN_FILE_HEADER))) {
    free(shx);
    DBUG_RETURN(NULL);
  }

  shx->flags    = flags;
  shx->fd       = 0;
  shx->filename = NULL;
  shx->header   = NULL;
  shx->mode     = '\0';
  shx->position = 0;
  shx->records  = 0;

  DBUG_RETURN(shx);
}

int shx_open(SHX *shx, char *shxfile, char mode)
{
  DBUG_ENTER("shx_open");
  DBUG_PRINT("info", ("SHX: Opening '%s', mode '%c'", shxfile, mode));

  shx->mode     = mode;
  shx->filename = strdup(shxfile);

  switch(mode) {
  case 'r':
    if((shx->fd = open(shxfile, O_RDONLY)) < 0) {
      fprintf(stderr, "Error opening SHX file for read: %i: %s\n",
	     errno, strerror(errno));
      DBUG_RETURN(-1);
    }

    if(_shx_read_header(shx) != 0) {
      DBUG_RETURN(-2);
    }

    shx_rewind(shx);
    break;

  case 'w':
    DBUG_RETURN(-254);
    break;

  default:
    fprintf(stderr, "SHX: Unknown mode '%c'\n", mode);
    DBUG_RETURN(-255);
  }

  DBUG_RETURN(shx->fd);
}

void shx_seek(SHX *shx, int pos)
{
  DBUG_ENTER("shx_seek");
  DBUG_PRINT("info", ("SHX: Seeking to offset %i", pos));
  lseek(shx->fd, pos, SEEK_SET);
  DBUG_VOID_RETURN;
}

void shx_seek_record(SHX *shx, uint32 record)
{
  DBUG_ENTER("shx_seek_record");
  DBUG_PRINT("info", ("SHX: Record seeking to record %i", record));
  shx_seek(shx, SHX_POS_DATA+(SHX_LEN_RECORD*record));
  shx->position = record;
  DBUG_VOID_RETURN;
}

void shx_rewind(SHX *shx)
{
  DBUG_ENTER("shx_rewind");
  shx_seek_record(shx, 0);
  DBUG_VOID_RETURN;
}

void shx_dump(SHX *shx)
{
  DBUG_ENTER("shx_dump");
  printf("\n");
  printf("SHX: Dump: 0x%08x\n", (int)shx);
  printf("  Structure:\n");
  printf("    header:     0x%08x\n", (int)shx->header);
  printf("    filename:   %s\n", shx->filename);
  printf("    fd:         %i\n", shx->fd);
  printf("    mode:       %c\n", shx->mode);
  printf("    flags:      %i\n", shx->flags);
  printf("    position:   %i\n", shx->position);
  printf("    records:    %i\n", shx->records);
  printf("  Header:\n");
  printf("    filecode:   %i\n", shx->header->filecode);
  printf("    unused1:    %i\n", shx->header->unused1);
  printf("    unused2:    %i\n", shx->header->unused2);
  printf("    unused3:    %i\n", shx->header->unused3);
  printf("    unused4:    %i\n", shx->header->unused4);
  printf("    unused5:    %i\n", shx->header->unused5);
  printf("    filelength: %i\n", shx->header->filelength);
  printf("    version:    %i\n", shx->header->version);
  printf("    shapetype:  %s (%i)\n", 
	 SHP_TYPES[shx->header->shapetype],
	 shx->header->shapetype);
  printf("    mbr_minx:   %+20.6f\n", shx->header->mbr_minx);
  printf("    mbr_miny:   %+20.6f\n", shx->header->mbr_miny);
  printf("    mbr_maxx:   %+20.6f\n", shx->header->mbr_maxx);
  printf("    mbr_maxy:   %+20.6f\n", shx->header->mbr_maxy);
  printf("    mbr_minz:   %+20.6f\n", shx->header->mbr_minz);
  printf("    mbr_maxz:   %+20.6f\n", shx->header->mbr_maxz);
  printf("    mbr_minm:   %+20.6f\n", shx->header->mbr_minm);
  printf("    mbr_maxm:   %+20.6f\n", shx->header->mbr_maxm);
  printf("\n\n");
  DBUG_VOID_RETURN;
}

void shx_record_dump(SHX_RECORD *record, int level)
{
  DBUG_ENTER("shx_record_dump");
  printf("Record:  Offset %10i  Length %10i\n",
	 record->offset, record->length);
  DBUG_VOID_RETURN;
}

void shx_record_free(SHX_RECORD *record)
{
  DBUG_ENTER("shx_record_free");
  free(record);
  DBUG_VOID_RETURN;
}

void shx_close(SHX *shx)
{
  DBUG_ENTER("shx_close");
  if(shx->fd) {
    close(shx->fd);
  }
  DBUG_VOID_RETURN;
}

void shx_free(SHX *shx)
{
  DBUG_ENTER("shx_free");
  if(shx) {
    if(shx->header)   free(shx->header);
    if(shx->filename) free(shx->filename);
    free(shx);
  }
  DBUG_VOID_RETURN;
}

