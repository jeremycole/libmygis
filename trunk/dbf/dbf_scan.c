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

#include "dbf_priv.h"

DBF_SCAN *dbf_scan_init(DBF *dbf, COMPARE *compare, char *key, char *value) {
  DBF_SCAN *scan;

  DBUG_ENTER("dbf_scan_init");
  DBUG_PRINT("info", ("DBF Scan: %s: '%s' %s '%s'",
		      compare?compare->name:NULL, key,
                      compare?compare->oper:NULL, value));

  if(!(scan = DBF_SCAN_INIT)) {
    fprintf(stderr, "DBF: Can't allocate memory for scan\n");
    return NULL;
  }
  scan->dbf     = dbf;
  scan->compare = compare;
  scan->key     = key?strdup(key):NULL;
  scan->value   = value?strdup(value):NULL;
  scan->last    = -1;

  DBUG_RETURN(scan);
}

int dbf_scan_next(DBF_SCAN *scan)
{
  DBF     *dbf     = scan->dbf;
  COMPARE *compare = scan->compare;
  RECORD *rec;
  int next_match = -1;

  DBUG_ENTER("dbf_scan_next");

  while(1) {
    if(!(rec = dbf_read_next(dbf))) {
      DBUG_PRINT("info", ("DBF Scan: End of file reached."));
      goto no_match;
    }
    if(!compare) goto match;
    if(compare->func(dbf_record_field(rec, scan->key), scan->value)) {
      DBUG_PRINT("info", ("DBF Scan: Found match at record %i, %s %s %s.",
			  dbf->position-1,
			  scan->key, compare->oper, scan->value));
      goto match;
    }
    DBUG_PRINT("info", ("DBF Scan: No match at record %i.",
			dbf->position-1));
  }      

 match:
  next_match = dbf->position-1;
  record_free(rec);

 no_match:
  DBUG_RETURN(scan->last = next_match);
}

RECORD *dbf_scan_read_next(DBF_SCAN *scan) {
  DBF *dbf = scan->dbf;
  int match;

  DBUG_ENTER("dbf_scan_read_next");

  if((match = dbf_scan_next(scan)) != -1) {
    dbf_record_seek(dbf, match);
    DBUG_RETURN(dbf_read_next(dbf));
  }
  DBUG_RETURN(NULL);
}

void dbf_scan_free(DBF_SCAN *scan)
{
  DBUG_ENTER("dbf_scan_free");
  free(scan);
  DBUG_VOID_RETURN;
}
