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

#ifndef DBF_H
#define DBF_H

#include <mygis/compare.h>
#include <mygis/record.h>

/* Possible field types
    C = Character (char *) <254 bytes, check DBF_FLD_LEN for length
    N = Number (double), 10 or 19 bytes long, text
    L = Logical (char), ?, Y, y, N, n, T, t, F, f
    D = Date (char *), 8 bytes long, YYYYMMDD
    F = Floating (double), 19 bytes long, text
    G = General, unsupported
    M = Memo, unsupported
    P = Picture, unsupported
*/

typedef enum dbf_field_type_en {
  DBF_CHARACTER        = 'C',
  DBF_NUMBER           = 'N',
  DBF_LOGICAL          = 'L',
  DBF_DATE             = 'D',
  DBF_FLOATING         = 'F',
  DBF_GENERAL          = 'G',
  DBF_MEMO             = 'M',
  DBF_PICTURE          = 'P'
} DBF_FIELD_TYPE;

typedef struct dbf_field_st {
  char            name[11];   /* name of field, max 10 characters plus null */
  DBF_FIELD_TYPE  type;       /* type of field, as above */
  byte            length;     /* digits before decimal point */
  byte            decimals;   /* digits after decimal point */
  byte            size;       /* total size to read from disk */
  char            format[10]; /* printf-compatible format string */
  METADATA        metadata;
} DBF_FIELD;

typedef struct dbf_st {
  char            *header;
  byte            version;
  int             numfields;
  DBF_FIELD       *fields;
  int             numrecords;
  int             record_length;
  char            *record_buffer;
  int             fd;
  char            *filename;
  int             flags;
  char            mode;
  int             position;
} DBF;

typedef struct dbf_scan_st {
  DBF             *dbf;
  COMPARE         *compare;
  char            *key;
  char            *value;
  int             last;
} DBF_SCAN;

#define FOREACH_DBF_FIELD(dbf, field, i) \
  for(field=dbf->fields, i=0; \
      i<dbf->numfields; \
      field++, i++)

DBF                 *dbf_init(int flags);
int                 dbf_open(DBF *dbf, char *dbffile, char mode);
void                dbf_seek(DBF *dbf, int pos);
void                dbf_seek_record(DBF *dbf, uint32 record);
RECORD              *dbf_read_next(DBF *dbf);
void                dbf_rewind(DBF *dbf);
void                dbf_dump(DBF *dbf);
void                dbf_close(DBF *dbf);
void                dbf_free(DBF *dbf);

DBF_SCAN            *dbf_scan_init(DBF *dbf, COMPARE *compare,
                                   char *key, char *value);
int                 dbf_scan_next(DBF_SCAN *scan);
RECORD              *dbf_scan_read_next(DBF_SCAN *scan);
void                dbf_scan_free(DBF_SCAN *scan);

char                *dbf_record_field(RECORD *record, char *key);

#endif /* DBF_H */
