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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiger.h"

#define TIGER_FILE_RECORD_HEADER \
  {"RT",        LEFT,  CHARACTER, NOTNULL,    1}, \
  {"VERSION",   LEFT,  CHARACTER, NOTNULL,    4}
  

TIGER_FILE_DEF tiger_file_def_rt1[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"SIDE1",     RIGHT, NUMBER,    MAYBENULL,  1},
  {"SOURCE",    LEFT,  CHARACTER, MAYBENULL,  1},
  {"FEDIRP",    LEFT,  CHARACTER, MAYBENULL,  2},
  {"FENAME",    LEFT,  CHARACTER, MAYBENULL, 30},
  {"FETYPE",    LEFT,  CHARACTER, MAYBENULL,  4},
  {"FEDIRS",    LEFT,  CHARACTER, MAYBENULL,  2},
  {"CFCC",      LEFT,  CHARACTER, NOTNULL,    3},
  {"FRADDL",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"TOADDL",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"FRADDR",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"TOADDR",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"FRIADDL",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"TOIADDL",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"FRIADDR",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"TOIADDR",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"ZIPL",      LEFT,  CHARACTER, MAYBENULL,  5},
  {"ZIPR",      LEFT,  CHARACTER, MAYBENULL,  5},
  {"AIANHHFPL", LEFT,  CHARACTER, MAYBENULL,  5},
  {"AIANHHFPR", LEFT,  CHARACTER, MAYBENULL,  5},
  {"AIHHTLIL",  LEFT,  CHARACTER, MAYBENULL,  1},
  {"AIHHTLIR",  LEFT,  CHARACTER, MAYBENULL,  1},
  {"CENSUS1",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"CENSUS2",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"STATEL",    LEFT,  NUMBER,    MAYBENULL,  2},
  {"STATER",    LEFT,  NUMBER,    MAYBENULL,  2},
  {"COUNTYL",   LEFT,  NUMBER,    MAYBENULL,  3},
  {"COUNTYR",   LEFT,  NUMBER,    MAYBENULL,  3},
  {"COUSUBL",   LEFT,  NUMBER,    MAYBENULL,  5},
  {"COUSUBR",   LEFT,  NUMBER,    MAYBENULL,  5},
  {"SUBMCDL",   LEFT,  NUMBER,    MAYBENULL,  5},
  {"SUBMCDR",   LEFT,  NUMBER,    MAYBENULL,  5},
  {"PLACEL",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"PLACER",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"TRACTL",    LEFT,  NUMBER,    MAYBENULL,  6},
  {"TRACTR",    LEFT,  NUMBER,    MAYBENULL,  6},
  {"BLOCKL",    LEFT,  NUMBER,    MAYBENULL,  4},
  {"BLOCKR",    LEFT,  NUMBER,    MAYBENULL,  4},
  {"FRLONG",    RIGHT, FLOAT1MM,  NOTNULL,   10},
  {"FRLAT",     RIGHT, FLOAT1MM,  NOTNULL,    9},
  {"TOLONG",    RIGHT, FLOAT1MM,  NOTNULL,   10},
  {"TOLAT",     RIGHT, FLOAT1MM,  NOTNULL,    9}
};

TIGER_FILE_DEF tiger_file_def_rt2[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, NUMBER,   NOTNULL,    10},
  {"RTSQ",      RIGHT, NUMBER,   NOTNULL,     3},
  {"LONG1",     RIGHT, FLOAT1MM, NOTNULL,    10},
  {"LAT1",      RIGHT, FLOAT1MM, NOTNULL,     9},
  {"LONG2",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT2",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG3",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT3",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG4",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT4",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG5",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT5",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG6",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT6",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG7",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT7",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG8",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT8",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG9",     RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT9",      RIGHT, FLOAT1MM, MAYBENULL,   9},
  {"LONG10",    RIGHT, FLOAT1MM, MAYBENULL,  10},
  {"LAT10",     RIGHT, FLOAT1MM, MAYBENULL,   9}
};

TIGER_FILE_DEF tiger_file_def_rt4[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, NUMBER,   NOTNULL,    10},
  {"RTSQ",      RIGHT, NUMBER,   NOTNULL,     3},
  {"FEAT1",     RIGHT, NUMBER,   NOTNULL,     8},
  {"FEAT2",     RIGHT, NUMBER,   MAYBENULL,   8},
  {"FEAT3",     RIGHT, NUMBER,   MAYBENULL,   8},
  {"FEAT4",     RIGHT, NUMBER,   MAYBENULL,   8},
  {"FEAT5",     RIGHT, NUMBER,   MAYBENULL,   8}
};

TIGER_FILE_DEF tiger_file_def_rt5[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  CHARACTER, NOTNULL,    5},
  {"FEAT",      RIGHT, NUMBER,    NOTNULL,    8},
  {"FEDIRP",    LEFT,  CHARACTER, MAYBENULL,  2},
  {"FENAME",    LEFT,  CHARACTER, MAYBENULL, 30},
  {"FETYPE",    LEFT,  CHARACTER, MAYBENULL,  4},
  {"FEDIRS",    LEFT,  CHARACTER, MAYBENULL,  2}
};

TIGER_FILE_DEF tiger_file_def_rt6[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, NUMBER,    NOTNULL,    3},
  {"FRADDL",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"TOADDL",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"FRADDR",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"TOADDR",    RIGHT, CHARACTER, MAYBENULL, 11},
  {"FRIADDL",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"TOIADDL",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"FRIADDR",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"TOIADDR",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"ZIPL",      LEFT,  CHARACTER, MAYBENULL,  5},
  {"ZIPR",      LEFT,  CHARACTER, MAYBENULL,  5}
};

TIGER_FILE_DEF tiger_file_def_rt7[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"LAND",      RIGHT, NUMBER,    NOTNULL,   10},
  {"SOURCE",    LEFT,  CHARACTER, MAYBENULL,  1},
  {"CFCC",      LEFT,  CHARACTER, NOTNULL,    3},
  {"LANAME",    LEFT,  CHARACTER, MAYBENULL, 30},
  {"LALONG",    RIGHT, FLOAT1MM,  MAYBENULL, 10},
  {"LALAT",     RIGHT, FLOAT1MM,  MAYBENULL,  9},
  {"FILLER",    LEFT,  CHARACTER, MAYBENULL,  1}
};

TIGER_FILE_DEF tiger_file_def_rt8[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, NUMBER,    NOTNULL,   10},
  {"LAND",      RIGHT, NUMBER,    NOTNULL,   10},
  {"FILLER",    LEFT,  CHARACTER, MAYBENULL,  1}
};


TIGER_FILE_DEF tiger_file_def_rta[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, NUMBER,    NOTNULL,   10},
  {"STATECU",   LEFT,  NUMBER,    NOTNULL,    2},
  {"COUNTYCU",  LEFT,  NUMBER,    NOTNULL,    3},
  {"TRACT",     LEFT,  NUMBER,    NOTNULL,    6},
  {"BLOCK",     LEFT,  NUMBER,    NOTNULL,    4},
  {"BLOCKSUFCU",LEFT,  CHARACTER, MAYBENULL,  1},
  {"RS-A1",     LEFT,  CHARACTER, MAYBENULL,  1},
  {"AIANHHFPCU",LEFT,  NUMBER,    MAYBENULL,  5},
  {"AIANHHCU",  LEFT,  NUMBER,    MAYBENULL,  4},
  {"AIHHTLICU", LEFT,  CHARACTER, MAYBENULL,  1},
  {"ANRCCU",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"AITSCECU",  LEFT,  NUMBER,    MAYBENULL,  3},
  {"AITSCU",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"CONCITCU",  LEFT,  NUMBER,    MAYBENULL,  5},
  {"COUSUBCU",  LEFT,  NUMBER,    NOTNULL,    5},
  {"SUBMCDCU",  LEFT,  NUMBER,    MAYBENULL,  5},
  {"PLACECU",   LEFT,  NUMBER,    MAYBENULL,  5},
  {"SDELMCU",   LEFT,  CHARACTER, MAYBENULL,  5},
  {"SDSECCU",   LEFT,  CHARACTER, MAYBENULL,  5},
  {"SDUNICU",   LEFT,  CHARACTER, MAYBENULL,  5},
  {"RS-A20",    LEFT,  NUMBER,    MAYBENULL,  4},
  {"RS-A21",    LEFT,  NUMBER,    MAYBENULL,  4},
  {"RS-A22",    LEFT,  NUMBER,    MAYBENULL,  4},
  {"CDCU",      RIGHT, NUMBER,    MAYBENULL,  2},
  {"ZCTA5CU",   LEFT,  CHARACTER, MAYBENULL,  5},
  {"ZCTA3CU",   RIGHT, CHARACTER, MAYBENULL,  3},
  {"RS-A4",     RIGHT, CHARACTER, MAYBENULL,  6},
  {"RS-A5",     RIGHT, CHARACTER, MAYBENULL,  3},
  {"RS-A6",     RIGHT, CHARACTER, MAYBENULL,  3},
  {"RS-A7",     RIGHT, CHARACTER, MAYBENULL,  5},
  {"RS-A8",     RIGHT, CHARACTER, MAYBENULL,  6},
  {"RS-A9",     RIGHT, CHARACTER, MAYBENULL,  6},
  {"CBSACU",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"NECTACU",   LEFT,  NUMBER,    MAYBENULL,  3},
  {"CNECTACU",  LEFT,  NUMBER,    MAYBENULL,  3},
  {"METDIVCU",  LEFT,  NUMBER,    MAYBENULL,  5},
  {"NECTADIVCU",LEFT,  NUMBER,    MAYBENULL,  5},
  {"RS-A14",    LEFT,  CHARACTER, MAYBENULL,  4},
  {"UACU",      LEFT,  NUMBER,    MAYBENULL,  5},
  {"URCU",      LEFT,  CHARACTER, MAYBENULL,  1},
  {"RS-A17",    LEFT,  CHARACTER, MAYBENULL,  6},
  {"RS-A18",    LEFT,  CHARACTER, MAYBENULL,  6},
  {"RS-A19",    LEFT,  CHARACTER, MAYBENULL, 11},
};

TIGER_FILE_DEF tiger_file_def_rtb[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, NUMBER,    NOTNULL,   10},
  {"STATECQ",   LEFT,  NUMBER,    NOTNULL,    2},
  {"COUNTYCQ",  LEFT,  NUMBER,    NOTNULL,    3},
  {"TRACTCQ",   LEFT,  NUMBER,    NOTNULL,    6},
  {"BLOCKCQ",   LEFT,  NUMBER,    NOTNULL,    5},
  {"AIANHHFPCQ",LEFT,  NUMBER,    MAYBENULL,  5},
  {"AIANHHCQ",  LEFT,  NUMBER,    MAYBENULL,  4},
  {"AIHHTLICQ", LEFT,  CHARACTER, MAYBENULL,  1},
  {"AITSCECQ",  LEFT,  NUMBER,    MAYBENULL,  3},
  {"AITSCQ",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"ANRCCQ",    LEFT,  NUMBER,    MAYBENULL,  5},
  {"CONCITCQ",  LEFT,  NUMBER,    MAYBENULL,  5},
  {"COUSUBCQ",  LEFT,  NUMBER,    NOTNULL,    5},
  {"SUBMCDCQ",  LEFT,  NUMBER,    MAYBENULL,  5},
  {"PLACECQ",   LEFT,  NUMBER,    MAYBENULL,  5},
  {"UACC",      LEFT,  NUMBER,    MAYBENULL,  5},
  {"URCC",      LEFT,  CHARACTER, MAYBENULL,  1},
  {"RS-B1",     LEFT,  CHARACTER, MAYBENULL,  8}
};

TIGER_FILE_DEF tiger_file_def_rtc[] = {
  TIGER_FILE_RECORD_HEADER,
  {"STATE",     LEFT,  NUMBER,    MAYBENULL,  2},
  {"COUNTY",    LEFT,  NUMBER,    MAYBENULL,  3},
  {"DATAYR",    LEFT,  CHARACTER, MAYBENULL,  4},
  {"FIPS",      LEFT,  NUMBER,    MAYBENULL,  5},
  {"FIPSCC",    LEFT,  CHARACTER, MAYBENULL,  2},
  {"PLACEDC",   LEFT,  CHARACTER, MAYBENULL,  1},
  {"LSADC",     LEFT,  CHARACTER, MAYBENULL,  2},
  {"ENTITY",    LEFT,  CHARACTER, NOTNULL,    1},
  {"MA",        LEFT,  NUMBER,    MAYBENULL,  4},
  {"SD",        LEFT,  NUMBER,    MAYBENULL,  5},
  {"AIANHH",    LEFT,  NUMBER,    MAYBENULL,  4},
  {"VTDTRACT",  RIGHT, CHARACTER, MAYBENULL,  6},
  {"UAUGA",     LEFT,  NUMBER,    MAYBENULL,  5},
  {"AITSCE",    LEFT,  NUMBER,    MAYBENULL,  3},
  {"CSACNECTA", LEFT,  NUMBER,    MAYBENULL,  3},
  {"CBSANECTA", LEFT,  NUMBER,    MAYBENULL,  5},
  {"COMMREG",   LEFT,  NUMBER,    MAYBENULL,  1},
  {"RS-C2",     LEFT,  NUMBER,    MAYBENULL,  1},
  {"NAME",      LEFT,  NUMBER,    MAYBENULL, 60}
};

TIGER_FILE_DEF tiger_file_def_rte[] = {
  TIGER_FILE_RECORD_HEADER
};

TIGER_FILE_DEF tiger_file_def_rth[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"TLID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"HIST",      LEFT,  CHARACTER, MAYBENULL,  1},
  {"SOURCE",    LEFT,  CHARACTER, MAYBENULL,  1},
  {"TLIDFR1",   RIGHT, NUMBER,    MAYBENULL, 10},
  {"TLIDFR2",   RIGHT, NUMBER,    MAYBENULL, 10},
  {"TLIDTO1",   RIGHT, NUMBER,    MAYBENULL, 10},
  {"TLIDTO2",   RIGHT, NUMBER,    MAYBENULL, 10}
};

TIGER_FILE_DEF tiger_file_def_rti[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"TLID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"TZIDS",     RIGHT, NUMBER,    NOTNULL,   10},
  {"TSIDE",     RIGHT, NUMBER,    NOTNULL,   10},
  {"CENIDL",    LEFT,  CHARACTER, MAYBENULL,  5},
  {"POLYIDL",   RIGHT, NUMBER,    MAYBENULL, 10},
  {"CENIDR",    LEFT,  CHARACTER, MAYBENULL,  5},
  {"POLYIDR",   RIGHT, NUMBER,    MAYBENULL, 10},
  {"SOURCEID",  LEFT,  CHARACTER, MAYBENULL, 10},
  {"FTSEG",     LEFT,  CHARACTER, MAYBENULL, 17},
  {"RS-I1",     LEFT,  CHARACTER, MAYBENULL, 10},
  {"RS-I2",     LEFT,  CHARACTER, MAYBENULL, 10},
  {"RS-I3",     LEFT,  CHARACTER, MAYBENULL, 10}
};

TIGER_FILE_DEF tiger_file_def_rtm[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, NUMBER,    NOTNULL,    3},
  {"SOURCEID",  LEFT,  CHARACTER, MAYBENULL, 10},
  {"ID",        LEFT,  CHARACTER, MAYBENULL, 18},
  {"IDFLAG",    RIGHT, CHARACTER, MAYBENULL,  1},
  {"RS-M1",     LEFT,  NUMBER,    MAYBENULL, 18},
  {"RS-M2",     LEFT,  CHARACTER, MAYBENULL,  2},
  {"RS-M3",     LEFT,  NUMBER,    MAYBENULL, 23}
};

TIGER_FILE_DEF tiger_file_def_rtp[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, NUMBER,    NOTNULL,   10},
  {"POLYLONG",  RIGHT, FLOAT1MM,  NOTNULL,   10},
  {"POLYLAT",   RIGHT, FLOAT1MM,  NOTNULL,    9},
  {"WATER",     LEFT,  NUMBER,    MAYBENULL,  1}
};

TIGER_FILE_DEF tiger_file_def_rtr[] = {
  TIGER_FILE_RECORD_HEADER
};

TIGER_FILE_DEF tiger_file_def_rts[] = {
  TIGER_FILE_RECORD_HEADER
};

TIGER_FILE_DEF tiger_file_def_rtt[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  NUMBER,    NOTNULL,    5},
  {"TZID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"SOURCE",    LEFT,  CHARACTER, MAYBENULL, 10},
  {"FTRP",      LEFT,  CHARACTER, MAYBENULL, 17}
};

TIGER_FILE_DEF tiger_file_def_rtu[] = {
  TIGER_FILE_RECORD_HEADER
};

TIGER_FILE_DEF tiger_file_def_rtz[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, NUMBER,    NOTNULL,    3},
  {"ZIP4L",     LEFT,  CHARACTER, MAYBENULL,  4},
  {"ZIP4R",     LEFT,  CHARACTER, MAYBENULL,  4}
};



TIGER_FILE_TYPES tiger_file_types[TIGER_MAX_FILE_TYPE] = {
  {RT1, "1", "Complete Chain Basic Data Record", {".RT1", ".rt1"},
   44, tiger_file_def_rt1
  },
  {RT2, "2", "Complete Chain Shape Coordinates", {".RT2", ".rt2"},
   24, tiger_file_def_rt2
  },
  {RT4, "4", "Index to Alternate Feature Identifiers", {".RT4", ".rt4"},
    9, tiger_file_def_rt4
  },
  {RT5, "5", "Complete Chain Feature Identifiers", {".RT5", ".rt5"},
    8, tiger_file_def_rt5
  },
  {RT6, "6", "Additional Address Range and ZIP Code Data", {".RT6", ".rt6"},
   14, tiger_file_def_rt6
  },
  {RT7, "7", "Landmark Features", {".RT7", ".rt7"},
   10, tiger_file_def_rt7
  },
  {RT8, "8", "Polygons Linked to Area Landmarks", {".RT8", ".rt8"},
    7, tiger_file_def_rt8
  },
  {RTA, "A", "Polygon Geographic Entity Codes: Current Geography", {".RTA",".rta"},
   47, tiger_file_def_rta
  },
  {RTB, "B", "Polygon Geographic Entity Codes: Corrections", {".RTB",".rtb"},
   22, tiger_file_def_rtb
  },
  {RTC, "C", "Geographic Entity Names", {".RTC",".rtc"},
   21, tiger_file_def_rtc
  },
  {RTE, "E", "Polygon Geographic Entity Codes: Economic Census", {".RTE",".rte"},
    2, tiger_file_def_rte
  },
  {RTH, "H", "TIGER/Line ID History", {".RTH",".rth"},
   10, tiger_file_def_rth
  },
  {RTI, "I", "Link Between Complete Chains and Polygons", {".RTI",".rti"},
   15, tiger_file_def_rti
  },
  {RTM, "M", "Feature Spatial Metadata Record", {".RTM",".rtm"},
   10, tiger_file_def_rtm
  },
  {RTP, "P", "Polygon Internal Point", {".RTP",".rtp"},
    8, tiger_file_def_rtp
  },
  {RTR, "R", "TIGER/Line ID Record Number Range", {".RTR",".rtr"},
    2, tiger_file_def_rtr
  },
  {RTS, "S", "Polygon Geographic Entity Codes: Census 2000", {".RTS",".rts"},
    2, tiger_file_def_rts
  },
  {RTT, "T", "TIGER Zero-Cell ID", {".RTT",".rtt"},
    6, tiger_file_def_rtt
  },
  {RTU, "U", "TIGER/Line ID Overpass/Underpass Identification", {".RTU",".rtu"},
    2, tiger_file_def_rtu
  },
  {RTZ, "Z", "ZIP+4 Codes", {".RTZ",".rtz"},
    6, tiger_file_def_rtz
  }
};

TIGER *tiger_init(int flags)
{
  TIGER            *tiger = NULL;
  TIGER_FILE       *file      = NULL;
  TIGER_FILE_TYPES *file_type = NULL;
  TIGER_FILE_DEF   *file_def  = NULL;
  uint type, field;

  DBUG_ENTER("tiger_init");

  if(!(tiger = TIGER_INIT))
    goto err1;

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file        = &tiger->files[type];
    file_type   = &tiger_file_types[type];

    file->type  = file_type->type;
    file->flags = flags;
    if(!(file->fixed = fixed_init(0))) {
      printf("Couldn't allocate fixed for file %i\n", type);
      goto err2;
    }
    for(field=0; field<file_type->num_fields; field++) {
      file_def = &file_type->file_def[field];
      fixed_append(file->fixed, 
                   fixed_field_new(file_def->name, file_def->padding,
		                   file_def->type, file_def->nulls,
				   file_def->length));
    }
  }

  DBUG_RETURN(tiger);

 err2:
  free(tiger);
 err1:
  DBUG_RETURN(NULL);
}

int tiger_open(TIGER *tiger, char *basename, char mode)
{
  TIGER_FILE       *file      = NULL;
  TIGER_FILE_TYPES *file_type = NULL;
  uint type;
  char *filename;

  DBUG_ENTER("tiger_open");

  if(!(filename = (char *) malloc(strlen(basename)+10)))
    DBUG_RETURN(1);

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file      = &tiger->files[type];
    file_type = &tiger_file_types[type];
    strcpy(filename, basename);
    strcat(filename, file_type->file_ext[0]);

    DBUG_PRINT("info", ("Attempting to open file %s", filename));
    fixed_open(file->fixed, filename, mode);
  }

  free(filename); 
  DBUG_RETURN(0);
}

void tiger_dump(TIGER *tiger)
{
  TIGER_FILE *file = NULL;
  uint type;
      
  DBUG_ENTER("tiger_dump");

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file = &tiger->files[type];
    fixed_dump(file->fixed);
  }
		        
  DBUG_VOID_RETURN;
}

void tiger_close(TIGER *tiger)
{
}

void tiger_free(TIGER *tiger)
{
  TIGER_FILE *file = NULL;
  uint type;

  DBUG_ENTER("tiger_free");

  for(type=0; type<TIGER_MAX_FILE_TYPE; type++) {
    file = &tiger->files[type];
    fixed_free(file->fixed);
  }

  free(tiger);

  DBUG_VOID_RETURN;
}

TIGER_RECORD *tiger_record_init(TIGER *tiger, TIGER_FILE_TYPE type)
{
  TIGER_RECORD *record;

  DBUG_ENTER("tiger_record_init");

  if(!(record = TIGER_RECORD_INIT))
    DBUG_RETURN(NULL);

  record->tiger = tiger;
  record->type  = type;
  record->fixed_record = NULL;

  DBUG_RETURN(record);
}

void tiger_record_dump(TIGER_RECORD *record)
{
  DBUG_ENTER("tiger_record_dump");
  fixed_record_dump(record->fixed_record);
  DBUG_VOID_RETURN;
}

void tiger_record_free(TIGER_RECORD *record)
{
  DBUG_ENTER("tiger_record_free");
  if(!record) DBUG_VOID_RETURN;
  fixed_record_free(record->fixed_record);
  free(record);
  DBUG_VOID_RETURN;
}
