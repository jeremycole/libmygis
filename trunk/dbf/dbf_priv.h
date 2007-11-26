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

#ifndef DBF_PRIV_H
#define DBF_PRIV_H

#include "mygis_priv.h"
#include "dbf.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define DBF_INIT                   MYGIS_MALLOC(DBF)
#define DBF_SCAN_INIT              MYGIS_MALLOC(DBF_SCAN)
#define DBF_FIELD_INIT(x)          MYGIS_MALLOC_X(DBF_FIELD, x)

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

int _dbf_read_header(DBF *dbf);

#endif /* DBF_PRIV_H */
