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

#include "tiger_defs.h"

#define TIGER_FILE_RECORD_HEADER \
  {"RT",        LEFT,  FIXED_CHARACTER, NOTNULL,    1}, \
  {"VERSION",   LEFT,  FIXED_CHARACTER, NOTNULL,    4}

FIXED_FILE_DEF tiger_file_def_rt1[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"SIDE1",     RIGHT, FIXED_NUMBER,    MAYBENULL,  1},
  {"SOURCE",    LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"FEDIRP",    LEFT,  FIXED_CHARACTER, MAYBENULL,  2},
  {"FENAME",    LEFT,  FIXED_CHARACTER, MAYBENULL, 30},
  {"FETYPE",    LEFT,  FIXED_CHARACTER, MAYBENULL,  4},
  {"FEDIRS",    LEFT,  FIXED_CHARACTER, MAYBENULL,  2},
  {"CFCC",      LEFT,  FIXED_CHARACTER, NOTNULL,    3},
  {"FRADDL",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"TOADDL",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"FRADDR",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"TOADDR",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"FRIADDL",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"TOIADDL",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"FRIADDR",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"TOIADDR",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"ZIPL",      LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"ZIPR",      LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"AIANHHFPL", LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"AIANHHFPR", LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"AIHHTLIL",  LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"AIHHTLIR",  LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"CENSUS1",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"CENSUS2",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"STATEL",    LEFT,  FIXED_NUMBER,    MAYBENULL,  2},
  {"STATER",    LEFT,  FIXED_NUMBER,    MAYBENULL,  2},
  {"COUNTYL",   LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"COUNTYR",   LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"COUSUBL",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"COUSUBR",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"SUBMCDL",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"SUBMCDR",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"PLACEL",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"PLACER",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"TRACTL",    LEFT,  FIXED_NUMBER,    MAYBENULL,  6},
  {"TRACTR",    LEFT,  FIXED_NUMBER,    MAYBENULL,  6},
  {"BLOCKL",    LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"BLOCKR",    LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"FRLONG",    RIGHT, FIXED_FLOAT1MM,  NOTNULL,   10},
  {"FRLAT",     RIGHT, FIXED_FLOAT1MM,  NOTNULL,    9},
  {"TOLONG",    RIGHT, FIXED_FLOAT1MM,  NOTNULL,   10},
  {"TOLAT",     RIGHT, FIXED_FLOAT1MM,  NOTNULL,    9}
};

FIXED_FILE_DEF tiger_file_def_rt2[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, FIXED_NUMBER,   NOTNULL,    10},
  {"RTSQ",      RIGHT, FIXED_NUMBER,   NOTNULL,     3},
  {"LONG1",     RIGHT, FIXED_FLOAT1MM, NOTNULL,    10},
  {"LAT1",      RIGHT, FIXED_FLOAT1MM, NOTNULL,     9},
  {"LONG2",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT2",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG3",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT3",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG4",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT4",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG5",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT5",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG6",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT6",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG7",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT7",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG8",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT8",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG9",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT9",      RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9},
  {"LONG10",    RIGHT, FIXED_FLOAT1MM, MAYBENULL,  10},
  {"LAT10",     RIGHT, FIXED_FLOAT1MM, MAYBENULL,   9}
};

FIXED_FILE_DEF tiger_file_def_rt4[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, FIXED_NUMBER,   NOTNULL,    10},
  {"RTSQ",      RIGHT, FIXED_NUMBER,   NOTNULL,     3},
  {"FEAT1",     RIGHT, FIXED_NUMBER,   NOTNULL,     8},
  {"FEAT2",     RIGHT, FIXED_NUMBER,   MAYBENULL,   8},
  {"FEAT3",     RIGHT, FIXED_NUMBER,   MAYBENULL,   8},
  {"FEAT4",     RIGHT, FIXED_NUMBER,   MAYBENULL,   8},
  {"FEAT5",     RIGHT, FIXED_NUMBER,   MAYBENULL,   8}
};

FIXED_FILE_DEF tiger_file_def_rt5[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"FEAT",      RIGHT, FIXED_NUMBER,    NOTNULL,    8},
  {"FEDIRP",    LEFT,  FIXED_CHARACTER, MAYBENULL,  2},
  {"FENAME",    LEFT,  FIXED_CHARACTER, MAYBENULL, 30},
  {"FETYPE",    LEFT,  FIXED_CHARACTER, MAYBENULL,  4},
  {"FEDIRS",    LEFT,  FIXED_CHARACTER, MAYBENULL,  2}
};

FIXED_FILE_DEF tiger_file_def_rt6[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, FIXED_NUMBER,    NOTNULL,    3},
  {"FRADDL",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"TOADDL",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"FRADDR",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"TOADDR",    RIGHT, FIXED_CHARACTER, MAYBENULL, 11},
  {"FRIADDL",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"TOIADDL",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"FRIADDR",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"TOIADDR",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"ZIPL",      LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"ZIPR",      LEFT,  FIXED_CHARACTER, MAYBENULL,  5}
};

FIXED_FILE_DEF tiger_file_def_rt7[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"LAND",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"SOURCE",    LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"CFCC",      LEFT,  FIXED_CHARACTER, NOTNULL,    3},
  {"LANAME",    LEFT,  FIXED_CHARACTER, MAYBENULL, 30},
  {"LALONG",    RIGHT, FIXED_FLOAT1MM,  MAYBENULL, 10},
  {"LALAT",     RIGHT, FIXED_FLOAT1MM,  MAYBENULL,  9},
  {"FILLER",    LEFT,  FIXED_DISCARD,   MAYBENULL,  1}
};

FIXED_FILE_DEF tiger_file_def_rt8[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"LAND",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"FILLER",    LEFT,  FIXED_DISCARD,   MAYBENULL,  1}
};


FIXED_FILE_DEF tiger_file_def_rta[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"STATECU",   LEFT,  FIXED_NUMBER,    NOTNULL,    2},
  {"COUNTYCU",  LEFT,  FIXED_NUMBER,    NOTNULL,    3},
  {"TRACT",     LEFT,  FIXED_NUMBER,    NOTNULL,    6},
  {"BLOCK",     LEFT,  FIXED_NUMBER,    NOTNULL,    4},
  {"BLOCKSUFCU",LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"RS-A1",     LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"AIANHHFPCU",LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"AIANHHCU",  LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"AIHHTLICU", LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"ANRCCU",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"AITSCECU",  LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"AITSCU",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"CONCITCU",  LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"COUSUBCU",  LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"SUBMCDCU",  LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"PLACECU",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"SDELMCU",   LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"SDSECCU",   LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"SDUNICU",   LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"RS-A20",    LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"RS-A21",    LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"RS-A22",    LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"CDCU",      RIGHT, FIXED_NUMBER,    MAYBENULL,  2},
  {"ZCTA5CU",   LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"ZCTA3CU",   RIGHT, FIXED_CHARACTER, MAYBENULL,  3},
  {"RS-A4",     RIGHT, FIXED_CHARACTER, MAYBENULL,  6},
  {"RS-A5",     RIGHT, FIXED_CHARACTER, MAYBENULL,  3},
  {"RS-A6",     RIGHT, FIXED_CHARACTER, MAYBENULL,  3},
  {"RS-A7",     RIGHT, FIXED_CHARACTER, MAYBENULL,  5},
  {"RS-A8",     RIGHT, FIXED_CHARACTER, MAYBENULL,  6},
  {"RS-A9",     RIGHT, FIXED_CHARACTER, MAYBENULL,  6},
  {"CBSACU",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"NECTACU",   LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"CNECTACU",  LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"METDIVCU",  LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"NECTADIVCU",LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"RS-A14",    LEFT,  FIXED_CHARACTER, MAYBENULL,  4},
  {"UACU",      LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"URCU",      LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"RS-A17",    LEFT,  FIXED_CHARACTER, MAYBENULL,  6},
  {"RS-A18",    LEFT,  FIXED_CHARACTER, MAYBENULL,  6},
  {"RS-A19",    LEFT,  FIXED_CHARACTER, MAYBENULL, 11},
};

FIXED_FILE_DEF tiger_file_def_rtb[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"STATECQ",   LEFT,  FIXED_NUMBER,    NOTNULL,    2},
  {"COUNTYCQ",  LEFT,  FIXED_NUMBER,    NOTNULL,    3},
  {"TRACTCQ",   LEFT,  FIXED_NUMBER,    NOTNULL,    6},
  {"BLOCKCQ",   LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"AIANHHFPCQ",LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"AIANHHCQ",  LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"AIHHTLICQ", LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"AITSCECQ",  LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"AITSCQ",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"ANRCCQ",    LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"CONCITCQ",  LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"COUSUBCQ",  LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"SUBMCDCQ",  LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"PLACECQ",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"UACC",      LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"URCC",      LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"RS-B1",     LEFT,  FIXED_CHARACTER, MAYBENULL,  8}
};

FIXED_FILE_DEF tiger_file_def_rtc[] = {
  TIGER_FILE_RECORD_HEADER,
  {"STATE",     LEFT,  FIXED_NUMBER,    MAYBENULL,  2},
  {"COUNTY",    LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"DATAYR",    LEFT,  FIXED_CHARACTER, MAYBENULL,  4},
  {"FIPS",      LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"FIPSCC",    LEFT,  FIXED_CHARACTER, MAYBENULL,  2},
  {"PLACEDC",   LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"LSADC",     LEFT,  FIXED_CHARACTER, MAYBENULL,  2},
  {"ENTITY",    LEFT,  FIXED_CHARACTER, NOTNULL,    1},
  {"MA",        LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"SD",        LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"AIANHH",    LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"VTDTRACT",  RIGHT, FIXED_CHARACTER, MAYBENULL,  6},
  {"UAUGA",     LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"AITSCE",    LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"CSACNECTA", LEFT,  FIXED_NUMBER,    MAYBENULL,  3},
  {"CBSANECTA", LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"COMMREG",   LEFT,  FIXED_NUMBER,    MAYBENULL,  1},
  {"RS-C2",     LEFT,  FIXED_NUMBER,    MAYBENULL,  1},
  {"NAME",      LEFT,  FIXED_NUMBER,    MAYBENULL, 60}
};

FIXED_FILE_DEF tiger_file_def_rte[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"STATEEC",   LEFT,  FIXED_NUMBER,    NOTNULL,    2},
  {"COUNTYEC",  LEFT,  FIXED_NUMBER,    NOTNULL,    3},
  {"RS-E1",     LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"RS-E2",     LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"PLACEEC",   LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"RS-E3",     LEFT,  FIXED_NUMBER,    MAYBENULL,  5},
  {"RS-E4",     LEFT,  FIXED_NUMBER,    MAYBENULL,  4},
  {"RS-E5",     LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"COMMREGEC", LEFT,  FIXED_NUMBER,    MAYBENULL,  1},
  {"RS-E6",     LEFT,  FIXED_CHARACTER, MAYBENULL, 17}
};

FIXED_FILE_DEF tiger_file_def_rth[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"TLID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"HIST",      LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"SOURCE",    LEFT,  FIXED_CHARACTER, MAYBENULL,  1},
  {"TLIDFR1",   RIGHT, FIXED_NUMBER,    MAYBENULL, 10},
  {"TLIDFR2",   RIGHT, FIXED_NUMBER,    MAYBENULL, 10},
  {"TLIDTO1",   RIGHT, FIXED_NUMBER,    MAYBENULL, 10},
  {"TLIDTO2",   RIGHT, FIXED_NUMBER,    MAYBENULL, 10}
};

FIXED_FILE_DEF tiger_file_def_rti[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"TLID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TZIDS",     RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TSIDE",     RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"CENIDL",    LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"POLYIDL",   RIGHT, FIXED_NUMBER,    MAYBENULL, 10},
  {"CENIDR",    LEFT,  FIXED_CHARACTER, MAYBENULL,  5},
  {"POLYIDR",   RIGHT, FIXED_NUMBER,    MAYBENULL, 10},
  {"SOURCEID",  LEFT,  FIXED_CHARACTER, MAYBENULL, 10},
  {"FTSEG",     LEFT,  FIXED_CHARACTER, MAYBENULL, 17},
  {"RS-I1",     LEFT,  FIXED_CHARACTER, MAYBENULL, 10},
  {"RS-I2",     LEFT,  FIXED_CHARACTER, MAYBENULL, 10},
  {"RS-I3",     LEFT,  FIXED_CHARACTER, MAYBENULL, 10}
};

FIXED_FILE_DEF tiger_file_def_rtm[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, FIXED_NUMBER,    NOTNULL,    3},
  {"SOURCEID",  LEFT,  FIXED_CHARACTER, MAYBENULL, 10},
  {"ID",        LEFT,  FIXED_CHARACTER, MAYBENULL, 18},
  {"IDFLAG",    RIGHT, FIXED_CHARACTER, MAYBENULL,  1},
  {"RS-M1",     LEFT,  FIXED_NUMBER,    MAYBENULL, 18},
  {"RS-M2",     LEFT,  FIXED_CHARACTER, MAYBENULL,  2},
  {"RS-M3",     LEFT,  FIXED_NUMBER,    MAYBENULL, 23}
};

FIXED_FILE_DEF tiger_file_def_rtp[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"POLYID",    RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"POLYLONG",  RIGHT, FIXED_FLOAT1MM,  NOTNULL,   10},
  {"POLYLAT",   RIGHT, FIXED_FLOAT1MM,  NOTNULL,    9},
  {"WATER",     LEFT,  FIXED_NUMBER,    MAYBENULL,  1}
};

FIXED_FILE_DEF tiger_file_def_rtr[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"CENID",     LEFT,  FIXED_CHARACTER, NOTNULL,    5},
  {"TLMAXID",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TLMINID",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TLHIGHID",  RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TZMAXID",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TZMINID",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TZHIGHID",  RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"FILLER",    LEFT,  FIXED_DISCARD,   MAYBENULL,  1}
};

FIXED_FILE_DEF tiger_file_def_rts[] = {
  TIGER_FILE_RECORD_HEADER
};

FIXED_FILE_DEF tiger_file_def_rtt[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"TZID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"SOURCE",    LEFT,  FIXED_CHARACTER, MAYBENULL, 10},
  {"FTRP",      LEFT,  FIXED_CHARACTER, MAYBENULL, 17}
};

FIXED_FILE_DEF tiger_file_def_rtu[] = {
  TIGER_FILE_RECORD_HEADER,
  {"FILE",      LEFT,  FIXED_NUMBER,    NOTNULL,    5},
  {"TZID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, FIXED_NUMBER,    NOTNULL,    1},
  {"TLIDOV1",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TLIDOV2",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TLIDUN1",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"TLIDUN2",   RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"FRLONG",    RIGHT, FIXED_FLOAT1MM,  NOTNULL,   10},
  {"FRLAT",     RIGHT, FIXED_FLOAT1MM,  NOTNULL,    9}
};

FIXED_FILE_DEF tiger_file_def_rtz[] = {
  TIGER_FILE_RECORD_HEADER,
  {"TLID",      RIGHT, FIXED_NUMBER,    NOTNULL,   10},
  {"RTSQ",      RIGHT, FIXED_NUMBER,    NOTNULL,    3},
  {"ZIP4L",     LEFT,  FIXED_CHARACTER, MAYBENULL,  4},
  {"ZIP4R",     LEFT,  FIXED_CHARACTER, MAYBENULL,  4}
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
   15, tiger_file_def_rte
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
   11, tiger_file_def_rtr
  },
  {RTS, "S", "Polygon Geographic Entity Codes: Census 2000", {".RTS",".rts"},
    2, tiger_file_def_rts
  },
  {RTT, "T", "TIGER Zero-Cell ID", {".RTT",".rtt"},
    6, tiger_file_def_rtt
  },
  {RTU, "U", "TIGER/Line ID Overpass/Underpass Identification", {".RTU",".rtu"},
   11, tiger_file_def_rtu
  },
  {RTZ, "Z", "ZIP+4 Codes", {".RTZ",".rtz"},
    6, tiger_file_def_rtz
  }
};