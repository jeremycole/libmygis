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

#include "shapefile_priv.h"

SHAPEFILE *shapefile_init(int flags)
{
  SHAPEFILE *shapefile;

  DBUG_ENTER("shapefile_init");

  if(!(shapefile = SHAPEFILE_INIT)) goto err1;
  if(!(shapefile->shp = shp_init(flags))) goto err2;
  if(!(shapefile->shx = shx_init(flags))) goto err3;
  if(!(shapefile->dbf = dbf_init(flags))) goto err4;
  if(!(shapefile->prj = prj_init(flags))) goto err5;

  shapefile->flags = flags;
  shapefile->projection = NULL;

  DBUG_RETURN(shapefile);

 err5:
  free(shapefile->dbf);
 err4:
  free(shapefile->shx);
 err3:
  free(shapefile->shp);
 err2:
  free(shapefile);
 err1:
  DBUG_RETURN(NULL);
}


int shapefile_open(SHAPEFILE *shapefile, char *basename, char mode)
{
  char *shpname, *shxname, *dbfname, *prjname;

  DBUG_ENTER("shapefile_open");
  DBUG_PRINT("info", ("SHAPEFILE: Opening '%s', mode '%c'", basename, mode));

  shapefile->mode     = mode;
  shapefile->basename = strdup(basename);

  if(!(shpname = (char *)malloc(strlen(basename)+5)))
  {
    fprintf(stderr, "Couldn't allocate memory for shpname\n");
    goto err1;
  }

  if(!(shxname = (char *)malloc(strlen(basename)+5)))
  {
    fprintf(stderr, "Couldn't allocate memory for shxname\n");
    goto err2;
  }

  if(!(dbfname = (char *)malloc(strlen(basename)+5)))
  {
    fprintf(stderr, "Couldn't allocate memory for dbfname\n");
    goto err3;
  }

  if(!(prjname = (char *)malloc(strlen(basename)+5)))
  {
    fprintf(stderr, "Couldn't allocate memory for prjname\n");
    goto err3;
  }

  strcpy(shpname, basename);
  strcat(shpname, ".shp");

  strcpy(shxname, basename);
  strcat(shxname, ".shx");

  strcpy(dbfname, basename);
  strcat(dbfname, ".dbf");

  strcpy(prjname, basename);
  strcat(prjname, ".prj");

  if(!(shapefile->flags & SHAPEFILE_NO_SHP))
  {
    if(shp_open(shapefile->shp, shpname, mode) < 0)
      goto err4;
    shapefile->flags |= SHAPEFILE_HAS_SHP;
    shp_set_projection(shapefile->shp, shapefile->projection);
  }

  if(!(shapefile->flags & SHAPEFILE_NO_SHX))
  {
    if(shx_open(shapefile->shx, shxname, mode) < 0)
      goto err5;
    shp_index(shapefile->shp, shapefile->shx);
    shapefile->flags |= SHAPEFILE_HAS_SHX;
  }

  if(!(shapefile->flags & SHAPEFILE_NO_DBF))
  {
    if(dbf_open(shapefile->dbf, dbfname, mode) < 0)
      goto err6;
    shapefile->flags |= SHAPEFILE_HAS_DBF;
  }

  if(!(shapefile->flags & SHAPEFILE_NO_PRJ))
  {
    if(prj_parse(shapefile->prj, prjname) < 0)
      goto err7;
    shapefile->flags |= SHAPEFILE_HAS_PRJ;
  }

  free(shpname);
  free(shxname);
  free(dbfname);
  free(prjname);

  DBUG_RETURN(0);

 err7:
  if(!(shapefile->flags & SHAPEFILE_NO_DBF))
    dbf_close(shapefile->dbf);
 err6:
  if(!(shapefile->flags & SHAPEFILE_NO_SHX))
    shx_close(shapefile->shx);
 err5:
  if(!(shapefile->flags & SHAPEFILE_NO_SHP))
    shp_close(shapefile->shp);
 err4:
  free(dbfname);
 err3:
  free(shxname);
 err2:
  free(shpname);
 err1:
  DBUG_RETURN(-1);
}

void shapefile_set_projection(SHAPEFILE *shapefile, PROJECTION *projection)
{
  shapefile->projection = projection;
  if(shapefile->flags & SHAPEFILE_HAS_SHP)
  {
    shp_set_projection(shapefile->shp, shapefile->projection);
  }
}

void shapefile_seek_record(SHAPEFILE *shapefile, uint32 record)
{
  DBUG_ENTER("shapefile_seek_record");
  DBUG_PRINT("info", ("SHAPEFILE: Record seeking to record %i", record));

  if(shapefile->flags & SHAPEFILE_HAS_SHP)
  {
    shp_seek_record(shapefile->shp, record);
  }

  if(shapefile->flags & SHAPEFILE_HAS_DBF)
  {
    dbf_seek_record(shapefile->dbf, record);
  }
  DBUG_VOID_RETURN;
}

SHAPEFILE_RECORD *shapefile_read_next(SHAPEFILE *shapefile)
{
  SHAPEFILE_RECORD *record;

  DBUG_ENTER("shapefile_read_next");

  if(!(record = SHAPEFILE_RECORD_INIT))
  {
    printf("error allocating memory\n");
    DBUG_RETURN(NULL);
  }

  record->shapefile = shapefile;
  record->geometry = NULL;
  record->dbf_record = NULL;

  if(shapefile->flags & SHAPEFILE_HAS_SHP)
  {
    record->geometry = shp_read_next(shapefile->shp);
  }

  if(shapefile->flags & SHAPEFILE_HAS_DBF)
  {
    record->dbf_record = dbf_read_next(shapefile->dbf);
  }

  if(shapefile->flags & SHAPEFILE_HAS_SHP
     && shapefile->flags & SHAPEFILE_HAS_DBF)
  {
    if(record->geometry == NULL && record->dbf_record != NULL)
    {
      fprintf(stderr, "DBF file contains more records than SHP\n");
      free(record->dbf_record);
      free(record);
      DBUG_RETURN(NULL);
    }

    if(record->geometry != NULL && record->dbf_record == NULL)
    {
      fprintf(stderr, "SHP file contains more records than DBF\n");
      free(record->geometry);
      free(record);
      DBUG_RETURN(NULL);
    }

    if(record->geometry == NULL && record->dbf_record == NULL)
    {
      /* OK, End of File */
      free(record);
      DBUG_RETURN(NULL);
    }
  }

  if((shapefile->flags & SHAPEFILE_HAS_SHP && record->geometry == NULL)
     || (shapefile->flags & SHAPEFILE_HAS_DBF && record->dbf_record == NULL))
  {
    /* OK, End of File */
    free(record);
    DBUG_RETURN(NULL);
  }

  DBUG_RETURN(record);
}

void shapefile_record_dump(SHAPEFILE_RECORD *record)
{
  DBUG_ENTER("shapefile_record_dump");
  if(record->dbf_record)
    record_dump(record->dbf_record);

  if(record->geometry)
    geometry_dump(record->geometry, 3);
  DBUG_VOID_RETURN;
}

void shapefile_record_free(SHAPEFILE_RECORD *record)
{
  DBUG_ENTER("shapefile_record_free");
  if(record->geometry)
    geometry_free(record->geometry);

  if(record->dbf_record)
    record_free(record->dbf_record);
  DBUG_VOID_RETURN;
}

void shapefile_dump(SHAPEFILE *shapefile)
{
  DBUG_ENTER("shapefile_dump");

  printf("\n");
  printf("SHAPEFILE: Dump: " PTR_FORMAT "\n", PTR_CAST(shapefile));
  printf("  Structure:\n");
  printf("    shp:        " PTR_FORMAT "\n", PTR_CAST(shapefile->shp));
  printf("    shx:        " PTR_FORMAT "\n", PTR_CAST(shapefile->shx));
  printf("    dbf:        " PTR_FORMAT "\n", PTR_CAST(shapefile->dbf));
  printf("    prj:        " PTR_FORMAT "\n", PTR_CAST(shapefile->prj));
  printf("    projection: " PTR_FORMAT "\n", PTR_CAST(shapefile->projection));
  printf("    basename:   %s\n", shapefile->basename);
  printf("    flags:      %i\n", shapefile->flags);
  printf("    mode:       %c\n", shapefile->mode);
  printf("\n\n");

  if(shapefile->projection)
    projection_dump(shapefile->projection);

  if(shapefile->flags & SHAPEFILE_HAS_SHP)
    shp_dump(shapefile->shp);

  if(shapefile->flags & SHAPEFILE_HAS_SHX)
    shx_dump(shapefile->shx);

  if(shapefile->flags & SHAPEFILE_HAS_DBF)
    dbf_dump(shapefile->dbf);

  if(shapefile->flags & SHAPEFILE_HAS_PRJ)
    prj_dump(shapefile->prj);

  DBUG_VOID_RETURN;
}

void shapefile_close(SHAPEFILE *shapefile)
{
  DBUG_ENTER("shapefile_close");
  if(shapefile->flags & SHAPEFILE_HAS_SHP)
    shp_close(shapefile->shp);

  if(shapefile->flags & SHAPEFILE_HAS_SHX)
    shx_close(shapefile->shx);

  if(shapefile->flags & SHAPEFILE_HAS_DBF)
    dbf_close(shapefile->dbf);
  DBUG_VOID_RETURN;
}

void shapefile_free(SHAPEFILE *shapefile)
{
  DBUG_ENTER("shapefile_free");

  free(shapefile->basename);

  shp_free(shapefile->shp);
  shx_free(shapefile->shx);
  dbf_free(shapefile->dbf);
  prj_free(shapefile->prj);
  free(shapefile);
  DBUG_VOID_RETURN;
}


SHAPEFILE_SCAN *shapefile_scan_init(SHAPEFILE *shapefile,
				    COMPARE *compare,
				    char *key, char *value)
{
  SHAPEFILE_SCAN *scan;

  DBUG_ENTER("shapefile_scan_init");
  DBUG_PRINT("info", ("Shapefile Scan: %s: '%s' %s '%s'",
		      compare?compare->name:NULL, key,
                      compare?compare->oper:NULL, value));

  if(!(scan = SHAPEFILE_SCAN_INIT))
  {
    fprintf(stderr, "SHAPEFILE: Couldn't allocate memory for scan\n");
    DBUG_RETURN(NULL);
  }

  scan->shapefile = shapefile;
  scan->compare = compare;

  if(shapefile->flags & SHAPEFILE_HAS_DBF &&
     (!(scan->dbf_scan = dbf_scan_init(shapefile->dbf, compare, key, value))))
    goto err;

  DBUG_RETURN(scan);

 err:
  free(scan);
  DBUG_RETURN(NULL);
}

SHAPEFILE_RECORD *shapefile_scan_read_next(SHAPEFILE_SCAN *scan)
{
  SHAPEFILE *shapefile = scan->shapefile;
  int match;

  DBUG_ENTER("shapefile_scan_read_next");

  if(shapefile->flags & SHAPEFILE_HAS_DBF)
  {
    if((match = dbf_scan_next(scan->dbf_scan)) != -1)
    {
      if(shapefile->flags & SHAPEFILE_HAS_SHP)
        shp_seek_record(shapefile->shp, match);
      dbf_seek_record(shapefile->dbf, match);
      DBUG_RETURN(shapefile_read_next(shapefile));
    }
  } else {
    DBUG_RETURN(shapefile_read_next(shapefile));
  }

  DBUG_RETURN(NULL);
}

void shapefile_scan_free(SHAPEFILE_SCAN *scan)
{
  DBUG_ENTER("shapefile_scan_free");
  if(scan->shapefile->flags & SHAPEFILE_HAS_DBF)
    dbf_scan_free(scan->dbf_scan);
  free(scan);
  DBUG_VOID_RETURN;
}
