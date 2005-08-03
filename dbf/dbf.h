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

/* http://www.cs.cornell.edu/Courses/cs212/2001fa/Project/Part1/dbf.htm */

#ifndef DBF_H
#define DBF_H

#include "mygis.h"
#include "../compare.h"

#define DBF_POS_FILE_HEADER         0
#define DBF_LEN_FILE_HEADER        32
#define DBF_LEN_FIELD              32

#define DBF_HDR_VERSION(x)         MYGIS_READ_BYTE((x)+0)
#define DBF_HDR_MOD_YY(x)          MYGIS_READ_BYTE((x)+1)
#define DBF_HDR_MOD_MM(x)          MYGIS_READ_BYTE((x)+2)
#define DBF_HDR_MOD_DD(x)          MYGIS_READ_BYTE((x)+3)
#define DBF_HDR_NUMRECORDS(x)      MYGIS_READ_UINT32_LE((x)+4)
#define DBF_HDR_LENHEADER(x)       MYGIS_READ_UINT16_LE((x)+8)
#define DBF_HDR_LENRECORD(x)       MYGIS_READ_UINT16_LE((x)+10)
#define DBF_HDR_RESERVED12(x)      MYGIS_READ_BYTE((x)+12)
#define DBF_HDR_RESERVED13(x)      MYGIS_READ_BYTE((x)+13)
#define DBF_HDR_INCOMPLETE_TRX(x)  MYGIS_READ_BYTE((x)+14)
#define DBF_HDR_ENCRYPTED(x)       MYGIS_READ_BYTE((x)+15)

#define DBF_FLD_NAME(x)            ((char *)(x))
#define DBF_FLD_TYPE(x)            ((char)*((char *)(x)+11))
#define DBF_FLD_ADDR(x)            MYGIS_READ_UINT32_LE((x)+12)
#define DBF_FLD_LEN(x)             MYGIS_READ_BYTE((x)+16)
#define DBF_FLD_DECIMALS(x)        MYGIS_READ_BYTE((x)+17)
#define DBF_FLD_RESERVED18(x)      MYGIS_READ_BYTE((x)+18)
#define DBF_FLD_RESERVED19(x)      MYGIS_READ_BYTE((x)+19)
#define DBF_FLD_WORKAREA(x)        MYGIS_READ_BYTE((x)+20)
#define DBF_FLD_RESERVED21(x)      MYGIS_READ_BYTE((x)+21)
#define DBF_FLD_RESERVED22(x)      MYGIS_READ_BYTE((x)+22)
#define DBF_FLD_SETFIELDS(x)       MYGIS_READ_BYTE((x)+23)
#define DBF_FLD_RESERVED24(x)      MYGIS_READ_BYTE((x)+24)
#define DBF_FLD_RESERVED25(x)      MYGIS_READ_BYTE((x)+25)
#define DBF_FLD_RESERVED26(x)      MYGIS_READ_BYTE((x)+26)
#define DBF_FLD_RESERVED27(x)      MYGIS_READ_BYTE((x)+27)
#define DBF_FLD_RESERVED28(x)      MYGIS_READ_BYTE((x)+28)
#define DBF_FLD_RESERVED29(x)      MYGIS_READ_BYTE((x)+29)
#define DBF_FLD_RESERVED30(x)      MYGIS_READ_BYTE((x)+30)
#define DBF_FLD_INDEXFIELD(x)      MYGIS_READ_BYTE((x)+31)

#define DBF_POS_DATA(x)            DBF_HDR_LENHEADER(x)

#define DBF_EOF                    0x1a  /* end of file */

#define DBF_FLD_STATUS_NORMAL      0x20  /* space   ' ' */
#define DBF_FLD_STATUS_DELETED     0x2a  /* asterix '*' */

#define DBF_HAS_INCOMPLETE_TRX     0x01
#define DBF_HAS_ENCRYPTED          0x01
#define DBF_FLD_HAS_INDEX          0x01

#define FOREACH_DBF_FIELD(dbf, field, i) \
  for(field=dbf->fields, i=0; \
      i<dbf->numfields; \
      field++, i++)

#define FOREACH_DBF_RECORD_FIELD_CELL(dbf_record, field, cell, i) \
  for(field=dbf_record->dbf->fields, cell = dbf_record->cells, i=0; \
      i<dbf_record->dbf->numfields; \
      field++, cell++, i++)

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
  CHARACTER        = 'C',
  NUMBER           = 'N',
  LOGICAL          = 'L',
  DATE             = 'D',
  FLOATING         = 'F',
  GENERAL          = 'G',
  MEMO             = 'M',
  PICTURE          = 'P'
} DBF_FIELD_TYPE;

typedef struct dbf_field_st {
  char            name[11];   /* name of field, max 10 characters plus null */
  DBF_FIELD_TYPE  type;       /* type of field, as above */
  byte            length;     /* digits before decimal point */
  byte            decimals;   /* digits after decimal point */
  byte            size;       /* total size to read from disk */
  char            format[10]; /* printf-compatible format string */
} DBF_FIELD;

typedef union dbf_cell_data_un {
  char            *character;
  double          number;
  char            logical;
  char            *date;
  double          floating;
} DBF_CELL_DATA;

typedef struct dbf_cell_st {
  DBF_FIELD       *field;
  DBF_CELL_DATA   data;
  char            status;
} DBF_CELL;

#define DBF_INIT                   MYGIS_MALLOC(DBF)
#define DBF_SCAN_INIT              MYGIS_MALLOC(DBF_SCAN)
#define DBF_RECORD_INIT            MYGIS_MALLOC(DBF_RECORD)
#define DBF_FIELD_INIT(x)          MYGIS_MALLOC_X(DBF_FIELD, x)
#define DBF_CELL_INIT(x)           MYGIS_MALLOC_X(DBF_CELL, x)


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

typedef struct dbf_record_st {
  DBF             *dbf;
  DBF_CELL        *cells;
  char            status;
} DBF_RECORD;

DBF                 *dbf_init(int flags);
int                 dbf_open(DBF *dbf, char *dbffile, char mode);
void                dbf_seek(DBF *dbf, int pos);
void                dbf_record_seek(DBF *dbf, uint32 record);
void                dbf_rewind(DBF *dbf);
void                dbf_dump(DBF *dbf);
void                dbf_close(DBF *dbf);
void                dbf_free(DBF *dbf);

DBF_SCAN            *dbf_scan_init(DBF *dbf, COMPARE *compare,
                                   char *key, char *value);
int                 dbf_scan_next(DBF_SCAN *scan);
DBF_RECORD          *dbf_scan_read_next(DBF_SCAN *scan);
void                dbf_scan_free(DBF_SCAN *scan);

DBF_RECORD          *dbf_read_next(DBF *dbf);
char                *dbf_record_field(DBF_RECORD *record, char *key);
void                dbf_record_dump(DBF_RECORD *record);
void                dbf_record_free(DBF_RECORD *record);

#endif /* DBF_H */
