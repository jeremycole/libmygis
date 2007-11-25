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

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "mygis.h"
#include "geometry.h"

#include "sh_header.h"
#include "shp.h"
#include "shp_priv.h"

const char SHP_TYPES[32][20] = {
  /*  0 */ {"NULL"},
  /*  1 */ {"POINT"},
  /*  2 */ { "" },
  /*  3 */ {"POLYLINE"},
  /*  4 */ { "" },
  /*  5 */ {"POLYGON"},
  /*  8 */ { "" },
  /*  7 */ { "" },
  /*  8 */ {"MULTIPOINT"},
  /*  9 */ { "" },
  /* 10 */ { "" },
  /* 11 */ {"POINTZ"},
  /* 12 */ { "" },
  /* 13 */ {"POLYLINEZ"},
  /* 14 */ { "" },
  /* 15 */ {"POLYGONZ"},
  /* 18 */ { "" },
  /* 17 */ { "" },
  /* 18 */ {"MULTIPOINTZ"},
  /* 19 */ { "" },
  /* 20 */ { "" },
  /* 21 */ {"POINTM"},
  /* 22 */ { "" },
  /* 23 */ {"POLYLINEM"},
  /* 24 */ { "" },
  /* 25 */ {"POLYGONM"},
  /* 28 */ { "" },
  /* 27 */ { "" },
  /* 28 */ {"MULTIPOINTM"},
  /* 29 */ { "" },
  /* 30 */ { "" },
  /* 31 */ {"MULTIPATCH"}
};

SHP *shp_init(int flags)
{
  SHP *shp;

  DBUG_ENTER("shp_init");

  if(!(shp = SHP_INIT)) {
    DBUG_RETURN(NULL);
  }

  shp->flags    = flags;
  shp->fd       = 0;
  shp->filename = NULL;
  shp->header   = NULL;
  shp->mode     = '\0';
  shp->index    = NULL;
  shp->position = 0;
  shp->records  = 0;

  DBUG_RETURN(shp);
}

int shp_open(SHP *shp, char *shpfile, char mode)
{
  DBUG_ENTER("shp_open");
  DBUG_PRINT("info", ("SHP: Opening '%s', mode '%c'", shpfile, mode));

  shp->mode     = mode;
  shp->filename = strdup(shpfile);

  switch(mode) {
  case 'r':
    if((shp->fd = open(shpfile, O_RDONLY)) < 0) {
      fprintf(stderr, "SHP: Error opening `%s' for read: Error %i: %s\n",
	      shpfile, errno, strerror(errno));
      DBUG_RETURN(-1);
    }
    if(_shp_read_header(shp)) {
      DBUG_RETURN(-2);
    }
    shp_rewind(shp);
    break;

  case 'w':
    if((shp->fd = open(shpfile, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG)) < 0) {
      fprintf(stderr, "SHP: Error opening `%s' for write: Error %i: %s\n",
	      shpfile, errno, strerror(errno));
      DBUG_RETURN(-1);
    }
    break;

  default:
    fprintf(stderr, "SHP: Unknown mode '%c'\n", mode);
    DBUG_RETURN(-255);
  }

  DBUG_RETURN(shp->fd);
}

void shp_set_projection(SHP *shp, PROJECTION *projection)
{
  shp->projection = projection;
}

void shp_index(SHP *shp, SHX *shx)
{
  DBUG_ENTER("shp_index");
  DBUG_PRINT("info", ("SHP: Associating Index 0x%08x", shx));
  if((shp->index = shx)) {
    shp->records = shp->index->records;
  }
  DBUG_VOID_RETURN;
}

void shp_seek(SHP *shp, int pos)
{
  DBUG_ENTER("shp_seek");
  DBUG_PRINT("info", ("SHP: Seeking to offset %i", pos));
  lseek(shp->fd, pos, SEEK_SET);
  DBUG_VOID_RETURN;
}

void shp_record_seek(SHP *shp, uint32 record)
{
  SHX_RECORD *rec;

  DBUG_ENTER("shp_record_seek");
  DBUG_PRINT("info", ("SHP: Record seeking to record %i", record));

  if(shp->index) {
    DBUG_PRINT("info", ("SHP: Have index, fast record seek"));
    shx_record_seek(shp->index, record);
    rec = shx_read_next(shp->index);
    shp_seek(shp, rec->offset);
    shx_record_free(rec);
  } else {
    DBUG_PRINT("info", ("SHP: No index, slow record seek"));
    shp_seek(shp, SHP_POS_DATA);
    for(;record;record--)
      shp_read_next(shp);
  }
  shp->position = record;

  DBUG_VOID_RETURN;
}

void shp_rewind(SHP *shp)
{
  DBUG_ENTER("shp_rewind");
  shp_record_seek(shp, 0);
  DBUG_VOID_RETURN;
}

void shp_dump(SHP *shp)
{
  POINT rpoint, tpoint;

  DBUG_ENTER("shp_dump");
  printf("\n");
  printf("SHP: Dump: " PTR_FORMAT "\n", PTR_CAST(shp));
  printf("  Structure:\n");
  printf("    header:     " PTR_FORMAT "\n", PTR_CAST(shp->header));
  printf("    index:      " PTR_FORMAT "\n", PTR_CAST(shp->index));
  printf("    projection: " PTR_FORMAT "\n", PTR_CAST(shp->projection));
  printf("    filename:   %s\n", shp->filename);
  printf("    fd:         %i\n", shp->fd);
  printf("    mode:       %c\n", shp->mode);
  printf("    flags:      %i\n", shp->flags);
  printf("    position:   %i\n", shp->position);
  printf("    records:    %i\n", shp->records);
  printf("  Header:\n");
  printf("    filecode:   %i\n", shp->header->filecode);
  printf("    unused1:    %i\n", shp->header->unused1);
  printf("    unused2:    %i\n", shp->header->unused2);
  printf("    unused3:    %i\n", shp->header->unused3);
  printf("    unused4:    %i\n", shp->header->unused4);
  printf("    unused5:    %i\n", shp->header->unused5);
  printf("    filelength: %i\n", shp->header->filelength);
  printf("    version:    %i\n", shp->header->version);
  printf("    shapetype:  %s (%i)\n", 
	 SHP_TYPES[shp->header->shapetype],
	 shp->header->shapetype);
  if(shp->projection)
  {
    rpoint.x = shp->header->mbr_minx; rpoint.y = shp->header->mbr_miny;
    tpoint = geometry_point_reproject(&rpoint, shp->projection);
    printf("    mbr_minx:   %+20.6f (reprojected)\n", tpoint.x);
    printf("    mbr_miny:   %+20.6f (reprojected)\n", tpoint.y);
    rpoint.x = shp->header->mbr_maxx; rpoint.y = shp->header->mbr_maxy;
    tpoint = geometry_point_reproject(&rpoint, shp->projection);
    printf("    mbr_maxx:   %+20.6f (reprojected)\n", tpoint.x);
    printf("    mbr_maxy:   %+20.6f (reprojected)\n", tpoint.y);
  } else {
    printf("    mbr_minx:   %+20.6f\n", shp->header->mbr_minx);
    printf("    mbr_miny:   %+20.6f\n", shp->header->mbr_miny);
    printf("    mbr_maxx:   %+20.6f\n", shp->header->mbr_maxx);
    printf("    mbr_maxy:   %+20.6f\n", shp->header->mbr_maxy);
  }
  printf("    mbr_minz:   %+20.6f\n", shp->header->mbr_minz);
  printf("    mbr_maxz:   %+20.6f\n", shp->header->mbr_maxz);
  printf("    mbr_minm:   %+20.6f\n", shp->header->mbr_minm);
  printf("    mbr_maxm:   %+20.6f\n", shp->header->mbr_maxm);
  printf("\n\n");
  DBUG_VOID_RETURN;
}

void shp_close(SHP *shp)
{
  DBUG_ENTER("shp_close");
  if(shp->fd) {
    close(shp->fd);
  }
  DBUG_VOID_RETURN;
}

void shp_free(SHP *shp)
{
  DBUG_ENTER("shp_free");
  if(shp) {
    if(shp->header)   free(shp->header);
    if(shp->filename) free(shp->filename);
    free(shp);
  }
  DBUG_VOID_RETURN;
}

