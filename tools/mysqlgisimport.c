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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>

#define _GNU_SOURCE
#include <getopt.h>

#include "mygis.h"
#include "pairlist.h"
#include "geometry.h"
#include "shapefile.h"
#include "wkt/wkt.h"

const char *program = {"mysqlgisimport"};
const char *version = {"0.1"};

static const char *short_options = {"?dDXSsnt:q:g:o:r:"};
static struct option long_options[] = {
  {"help",           no_argument,       NULL, '?'},
#ifdef DEBUG
  {"debug",          optional_argument, NULL, 'd'},
#endif
  {"no-dbf",         no_argument,       NULL, 'D'},
  {"no-shx",         no_argument,       NULL, 'X'},
  {"no-shp",         no_argument,       NULL, 'S'},
  {"no-schema",      no_argument,       NULL, 's'},
  {"no-data",        no_argument,       NULL, 'n'},
  {"table",          required_argument, NULL, 't'},
  {"query",          required_argument, NULL, 'q'},
  {"geometry-field", required_argument, NULL, 'g'},
  {"output",         required_argument, NULL, 'o'},
  {"remap",          required_argument, NULL, 'r'},
  {0, 0, 0, 0}
};

void usage(FILE *f)
{
  DBUG_ENTER("usage");
  fprintf(f, "\n");
  fprintf(f, "%s %s, %s\n", program, version, mygis_version);
  fprintf(f, "%s\n", mygis_copyright);
  fprintf(f, "Distributed under the %s\n", mygis_license);
  fprintf(f, "\n");
  fprintf(f, "Usage: %s [options] </path/to/shapefiles>\n", program);
  fprintf(f, "  -?, --help          Display this help and exit.\n");
#ifdef DEBUG
  fprintf(f, "  -d, --debug         Output debugging information while running.\n");
#endif
  fprintf(f, "  -D, --no-dbf        Don't use a DBF (database) file.\n");
  fprintf(f, "  -S, --no-shp        Don't use a SHP (shape) file, implies --no-shx.\n");
  fprintf(f, "  -X, --no-shx        Don't use a SHX (shape index) file.\n");
  fprintf(f, "  -s, --no-schema     Don't output any schema, only the data.\n");
  fprintf(f, "  -n, --no-data       Don't output any data, only the schema.\n");
  fprintf(f, "  -t, --table         Table name to load records into.\n");
  fprintf(f, "  -q, --query         DBF query of form: \"FIELD=value\".\n");
  fprintf(f, "  -g, --geometry-field Name of GEOMETRY field, default `geo`.\n");
  fprintf(f, "  -o, --output        Output to a file, default stdout.\n");
  fprintf(f, "  -r, --remap         Remap a DBF column to a another name.\n");
  fprintf(f, "                      Expects `dbf_name=new_name' as an argument.\n");
  fprintf(f, "\n");
  DBUG_VOID_RETURN;
}

char *sql_table_name(char *name)
{
  static char sql[200];

  DBUG_ENTER("sql_table_name");
  sprintf(sql, "`%s`", name);
  DBUG_RETURN(sql);
}

char *sql_field_name(DBF_FIELD *field, PAIRLIST *remap)
{
  static char sql[200];

  DBUG_ENTER("sql_field_name");
  /* TODO: Need to do some cleanup of the field name. */
  sprintf(sql, "`%s`", pairlist_get_value(remap, field->name));
  DBUG_RETURN(sql);
}

char *sql_field_type(DBF_FIELD *field)
{
  static char sql[200];

  DBUG_ENTER("sql_field_type");

  if(!field) DBUG_RETURN(NULL);

  switch(field->type) {
  case CHARACTER:
    sprintf(sql, "CHAR(%i) NOT NULL", field->length);
    break;
  case DATE:
    sprintf(sql, "DATE NOT NULL");
    break;
  case NUMBER:
    sprintf(sql, "INT NOT NULL");
    break;
  case FLOATING:
    sprintf(sql, "FLOAT NOT NULL");
    break;
  case LOGICAL:
    sprintf(sql, "CHAR(1) NOT NULL");
    break;
  }
  DBUG_RETURN(sql);
}

char *sql_field_value(DBF_FIELD *field, DBF_CELL *cell)
{
  static char sql[200];

  DBUG_ENTER("sql_field_value");

  /* TODO: Need to escape the data for SQL. */

  if(!field || !cell) DBUG_RETURN(NULL);
		      
  switch(field->type) {
  case CHARACTER:
    sprintf(sql, "\"%s\"", cell->data.character);
    break;
  case DATE:
    sprintf(sql, "\"%s\"", cell->data.date);
    break;
  case NUMBER:
    sprintf(sql, "%li", cell->data.number);
    break;
  case FLOATING:
    sprintf(sql, "%f", cell->data.floating);
    break;
  case LOGICAL:
    sprintf(sql, "\"%c\"", cell->data.logical);
    break;
  }
  DBUG_RETURN(sql);
}

void print_schema(FILE *f, SHAPEFILE *sha, 
                  char *table_name, char *geometry_field,
		  PAIRLIST *remap)
{
  DBF *dbf = sha->dbf;
  DBF_FIELD *field;
  int i;

  DBUG_ENTER("print_schema");

  fprintf(f, "DROP TABLE IF EXISTS `%s`;\n", table_name);
  fprintf(f, "CREATE TABLE `%s` (\n", table_name);
  fprintf(f, "  %-20s INT UNSIGNED NOT NULL auto_increment,\n", "`id`");

  if(sha->flags & SHAPEFILE_HAS_DBF) {
    FOREACH_DBF_FIELD(dbf, field, i) {
      fprintf(f, "  %-20s %s,\n", sql_field_name(field, remap), sql_field_type(field));
    }
  }

  if(sha->flags & SHAPEFILE_HAS_SHP) {
    fprintf(f, "  %-20s GEOMETRY NOT NULL,\n", geometry_field);
    fprintf(f, "  PRIMARY KEY (id),\n");
    fprintf(f, "  SPATIAL INDEX (%s)\n", geometry_field);
  } else {
    fprintf(f, "  PRIMARY KEY (id)\n");
  }

  fprintf(f, ");\n\n");

  DBUG_VOID_RETURN;
}

void print_record(FILE *f, SHAPEFILE_RECORD *record, char *table_name)
{
  SHAPEFILE *sha = record->shapefile;
  DBF_RECORD *dbf_record = record->dbf_record;
  DBF_FIELD *field;
  DBF_CELL *cell;
  int i;

  DBUG_ENTER("print_record");

  fprintf(f, "INSERT INTO `%s` VALUES (NULL", table_name);
  if(sha->flags & SHAPEFILE_HAS_DBF) {
    FOREACH_DBF_RECORD_FIELD_CELL(dbf_record, field, cell, i) {
      fprintf(f, ", %s", sql_field_value(field, cell));
    }
  }
  if(sha->flags & SHAPEFILE_HAS_SHP) {
    fprintf(f, ", GEOMFROMTEXT(\"");
    wkt_write(record->geometry, f);
    fprintf(f, "\")\n");
  }
  fprintf(f, ");\n");

  DBUG_VOID_RETURN;
}

SHAPEFILE_SCAN *scan_query(SHAPEFILE *sha, char *query)
{
  SHAPEFILE_SCAN *scan = NULL;
  char *key, *value, *p;

  DBUG_ENTER("scan_query");

  if((p=index(query, '='))) {
    key = query;
    *p = '\0';
    value = ++p;
    scan = shapefile_scan_init(sha, &compare_string_ci_eq, key, value);
  } else {
    fprintf(stderr, "Bad query format '%s', should be of the form 'key=value'.", query);
    DBUG_RETURN(NULL);
  }
  DBUG_RETURN(scan);
}

int main(int argc, char **argv)
{
  SHAPEFILE *sha;
  SHAPEFILE_SCAN *scan;
  SHAPEFILE_RECORD *rec;
  int shapefile_flags = 0;
  int ret = 0;

  FILE *output = stdout;

  PAIRLIST *remap = NULL;
  DBF_FIELD *field;
  int i;

  int opt, option_index;
  int opt_no_schema = 0;
  int opt_no_data   = 0;

  char *table_name = NULL;
  char *geometry_field = {"`geo`"};
  char *query = NULL;
  char *ptr = NULL;

  DBUG_ENTER("main");
  DBUG_PROCESS(argv[0]);

  if(!(remap = pairlist_init(&compare_string_ci_eq, &compare_string_ci_eq)))
    DBUG_RETURN(1);

  while(1) {
    opt = getopt_long(argc, argv, short_options, long_options, &option_index);
    if (opt == -1) break;

    switch(opt) {
    case '?':
      usage(stdout);
      DBUG_RETURN(0);
    case 'd':
      DBUG_PUSH(optarg?optarg:"d:t");
      break;
    case 'D':
      shapefile_flags |= SHAPEFILE_NO_DBF;
      break;
    case 'S':
      shapefile_flags |= SHAPEFILE_NO_SHP|SHAPEFILE_NO_SHX;
      break;
    case 'X':
      shapefile_flags |= SHAPEFILE_NO_SHX;
      break;
    case 's':
      opt_no_schema++;
      break;
    case 'n':
      opt_no_data++;
      break;
    case 't':
      table_name = (char *)strdup(optarg);
      break;
    case 'q':
      query = (char *)strdup(optarg);
      break;
    case 'g':
      geometry_field = (char *)strdup(optarg);
      break;
    case 'o':
      if(optarg[0] == '-' && optarg[1] == '\0') break;
      if(!(output = fopen(optarg, "w"))) {
        fprintf(stderr, "Couldn't open output file `%s': Error %i: %s",
	        optarg, errno, strerror(errno));
        goto err1;
      break;
    case 'r':
      if(!(ptr=strchr(optarg, '=')))
        goto err1;
      *ptr++ = '\0';
      pairlist_add(remap, optarg, ptr); 
      break;
      }
    }
  }

  if(optind == argc) {
    usage(stderr);
    ret = 1; goto err1;
  }

  if((shapefile_flags & SHAPEFILE_NO_DBF) &&
     (shapefile_flags & SHAPEFILE_NO_SHP)) {
    fprintf(stderr, "ERROR: You must have either a .shp or .dbf file.\n");
    ret = 1; goto err1;
  }

  if(!(sha = shapefile_init(shapefile_flags))) {
    fprintf(stderr, "Couldn't initialize, out of memory?\n");
    ret = 2; goto err1;
  }

  if(shapefile_open(sha, argv[optind], 'r') < 0) {
    fprintf(stderr, "Couldn't open files, missing files?\n");
    ret = 3; goto err2;
  }
  
  if(!table_name) table_name = (char *)strdup(basename(argv[optind]));

  if(sha->flags & SHAPEFILE_HAS_DBF) {
    FOREACH_DBF_FIELD(sha->dbf, field, i) {
      if(!pairlist_get(remap, field->name))
        pairlist_add(remap, field->name, field->name);
    }
  }

  if(!opt_no_schema)
    print_schema(output, sha, table_name, geometry_field, remap);

  if(!opt_no_data) {
    if(query) {
      if(!(scan = scan_query(sha, query))) goto err3;
    } else {
      scan = shapefile_scan_init(sha, NULL, NULL, NULL);
    }
    while((rec = shapefile_scan_read_next(scan))) {
      print_record(output, rec, table_name);
      shapefile_record_free(rec);
    } 
    shapefile_scan_free(scan);
  }

 err3:
  shapefile_close(sha);
 err2:
  shapefile_free(sha);
 err1:
  pairlist_free(remap);
  DBUG_RETURN(ret);
}
