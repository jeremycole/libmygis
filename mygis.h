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

#ifndef MYGIS_H
#define MYGIS_H

#define _GNU_SOURCE

#include "config.h"

#ifndef DEBUG
#define DBUG_OFF
#endif

#include "dbug.h"
#include "portability.h"

extern const char *mygis_version;
extern const char *mygis_copyright;
extern const char *mygis_license;

typedef unsigned char      byte;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef signed char        sint8;
typedef signed short       sint16;
typedef signed int         sint32;
typedef signed long long   sint64;

#define SZ_SHORT  (2)
#define SZ_UINT32 (4)
#define SZ_UINT64 (8)

#define SZ_FLOAT  (4)
#define SZ_DOUBLE (8)

/* Useful Macros */

#define MIN(x, y)                    (((x)<(y))?(x):(y))
#define MAX(x, y)                    (((x)>(y))?(x):(y))

#define MIN_NOTE(m, x, y, n, v)      \
  { if(x<y) { m = x; n = v; } }

#define MAX_NOTE(m, x, y, n, v)      \
  { if(x>y) { m = x; n = v; } }

#define SWAP(x, y)                   { (x) ^= (y) ^= (x) ^= (y); }


/* 

Various macros for swapping a certain number of bytes.

Note that when swapping odd numbers of bytes, the middle byte is untouched.

*/


#define MYGIS_SWAP2(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[1]); \
}

#define MYGIS_SWAP3(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[2]); \
}

#define MYGIS_SWAP4(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[3]); \
  SWAP(((byte *)(pos))[1], ((byte *)(pos))[2]); \
}

#define MYGIS_SWAP5(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[4]); \
  SWAP(((byte *)(pos))[1], ((byte *)(pos))[3]); \
}

#define MYGIS_SWAP6(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[5]); \
  SWAP(((byte *)(pos))[1], ((byte *)(pos))[4]); \
  SWAP(((byte *)(pos))[2], ((byte *)(pos))[3]); \
}

#define MYGIS_SWAP7(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[6]); \
  SWAP(((byte *)(pos))[1], ((byte *)(pos))[5]); \
  SWAP(((byte *)(pos))[2], ((byte *)(pos))[4]); \
}

#define MYGIS_SWAP8(pos)       { \
  SWAP(((byte *)(pos))[0], ((byte *)(pos))[7]); \
  SWAP(((byte *)(pos))[1], ((byte *)(pos))[6]); \
  SWAP(((byte *)(pos))[2], ((byte *)(pos))[5]); \
  SWAP(((byte *)(pos))[3], ((byte *)(pos))[4]); \
}


/* Useful macros to the developer. */

#define MYGIS_SWAP_UINT16(pos)       MYGIS_SWAP2(pos)
#define MYGIS_SWAP_UINT32(pos)       MYGIS_SWAP4(pos)
#define MYGIS_SWAP_UINT64(pos)       MYGIS_SWAP8(pos)

#define MYGIS_SWAP_FLOAT(pos)        MYGIS_SWAP4(pos)
#define MYGIS_SWAP_DOUBLE(pos)       MYGIS_SWAP8(pos)

/* 

These functions either swap the bytes of their argument, or no-op,
depending on the endianness of the host architecture.

They kind of "assert" that their argument should be big or little
endian and a certain type.  The appropriate action or inaction is
taken automatically, modifying the argument in place.

Also note that since these macros end up modifying their arguments,
if they are accidentally or purposely called with the same argument
more than once, they will gladly modify the argument again.

*/

#ifndef BIGENDIAN
#define MYGIS_LE_UINT16(pos)         {}
#define MYGIS_LE_UINT32(pos)         {}
#define MYGIS_LE_UINT64(pos)         {}
#define MYGIS_LE_FLOAT(pos)          {}
#define MYGIS_LE_DOUBLE(pos)         {}
#define MYGIS_BE_UINT16(pos)         MYGIS_SWAP_UINT16(pos)
#define MYGIS_BE_UINT32(pos)         MYGIS_SWAP_UINT32(pos)
#define MYGIS_BE_UINT64(pos)         MYGIS_SWAP_UINT64(pos)
#define MYGIS_BE_FLOAT(pos)          MYGIS_SWAP_FLOAT(pos)
#define MYGIS_BE_DOUBLE(pos)         MYGIS_SWAP_DOUBLE(pos)
#else
#define MYGIS_LE_UINT16(pos)         MYGIS_SWAP_UINT16(pos)
#define MYGIS_LE_UINT32(pos)         MYGIS_SWAP_UINT32(pos)
#define MYGIS_LE_UINT64(pos)         MYGIS_SWAP_UINT64(pos)
#define MYGIS_LE_FLOAT(pos)          MYGIS_SWAP_FLOAT(pos)
#define MYGIS_LE_DOUBLE(pos)         MYGIS_SWAP_DOUBLE(pos)
#define MYGIS_BE_UINT16(pos)         {}
#define MYGIS_BE_UINT32(pos)         {}
#define MYGIS_BE_UINT64(pos)         {}
#define MYGIS_BE_FLOAT(pos)          {}
#define MYGIS_BE_DOUBLE(pos)         {}
#endif

/*

Macros for casting and dereferencing an arbitrary pointer to a
certain type in order to read the value at the pointer destination.

These could be used by themselves, but their main purpose is to
be used in the macros below, which deal with endianness properly.

*/

#define MYGIS_READ_BYTE(pos)         ((byte)*((byte *)(pos)))
#define MYGIS_READ_UINT16(pos)       ((uint16)*((uint16 *)(pos)))
#define MYGIS_READ_UINT32(pos)       ((uint32)*((uint32 *)(pos)))
#define MYGIS_READ_UINT64(pos)       ((uint64)*((uint64 *)(pos)))
#define MYGIS_READ_FLOAT(pos)        ((float)*((float *)(pos)))
#define MYGIS_READ_DOUBLE(pos)       ((double)*((double *)(pos)))

/*

Macros to read the value of a certain type, with a certain endianness,
pointed to by an arbitrary pointer.

If the value being read is the same endianness as the host architecture,
these are extremely efficient macros, that just dereference the pointer.

If the value being read is a different endianness than the host is,
swapping the bytes will incur a function call.

*/

#ifndef BIGENDIAN
#define MYGIS_READ_UINT16_LE(pos)    MYGIS_READ_UINT16(pos) 
#define MYGIS_READ_UINT32_LE(pos)    MYGIS_READ_UINT32(pos)
#define MYGIS_READ_UINT64_LE(pos)    MYGIS_READ_UINT64(pos)
#define MYGIS_READ_FLOAT_LE(pos)     MYGIS_READ_FLOAT(pos)
#define MYGIS_READ_DOUBLE_LE(pos)    MYGIS_READ_DOUBLE(pos)
#define MYGIS_READ_UINT16_BE(pos)    mygis_swap_uint16(MYGIS_READ_UINT16(pos))
#define MYGIS_READ_UINT32_BE(pos)    mygis_swap_uint32(MYGIS_READ_UINT32(pos))
#define MYGIS_READ_UINT64_BE(pos)    mygis_swap_uint64(MYGIS_READ_UINT64(pos))
#define MYGIS_READ_FLOAT_BE(pos)     mygis_swap_float(MYGIS_READ_FLOAT(pos))
#define MYGIS_READ_DOUBLE_BE(pos)    mygis_swap_double(MYGIS_READ_DOUBLE(pos))
#else
#define MYGIS_READ_UINT16_BE(pos)    MYGIS_READ_UINT16(pos)
#define MYGIS_READ_UINT32_BE(pos)    MYGIS_READ_UINT32(pos)
#define MYGIS_READ_UINT64_BE(pos)    MYGIS_READ_UINT64(pos)
#define MYGIS_READ_FLOAT_BE(pos)     MYGIS_READ_FLOAT(pos)
#define MYGIS_READ_DOUBLE_BE(pos)    MYGIS_READ_DOUBLE(pos)
#define MYGIS_READ_UINT16_LE(pos)    mygis_swap_uint16(MYGIS_READ_UINT16(pos))
#define MYGIS_READ_UINT32_LE(pos)    mygis_swap_uint32(MYGIS_READ_UINT32(pos))
#define MYGIS_READ_UINT64_LE(pos)    mygis_swap_uint64(MYGIS_READ_UINT64(pos))
#define MYGIS_READ_FLOAT_LE(pos)     mygis_swap_float(MYGIS_READ_FLOAT(pos))
#define MYGIS_READ_DOUBLE_LE(pos)    mygis_swap_double(MYGIS_READ_DOUBLE(pos))
#endif /* BIGENDIAN */


#define MYGIS_MALLOC(t)          ( (t *)malloc(sizeof(t)) )
#define MYGIS_MALLOC_X(t, x)     ( (t *)malloc((x)*sizeof(t)) )

#define MYGIS_REALLOC(p, t)      ( (t *)realloc((p), sizeof(t)) )
#define MYGIS_REALLOC_X(p, t, x) ( (t *)realloc((p), (x)*sizeof(t)) )


#define MYGIS_APPEND_NODE(object, node)        \
{                                              \
  if((object)->head == NULL) {                 \
    (object)->head = (object)->tail = (node);  \
    (node)->prev  = (node)->next  = NULL;      \
  } else {                                     \
    (object)->tail->next = (node);             \
    (node)->prev = (object)->tail;             \
    (node)->next = NULL;                       \
    (object)->tail = (node);                   \
  }                                            \
}

#define MYGIS_REMOVE_NODE(object, node)        \
{                                              \
  if((object)->head == (node))                 \
    (object)->head = (node)->next;             \
  if((object)->tail == (node))                 \
    (object)->tail = (node)->prev;             \
  if((node)->prev)                             \
    (node)->prev->next = (node)->next;         \
  if((node)->next)                             \
    (node)->next->prev = (node)->prev;         \
}

/*

PUBLIC FUNCTIONS

*/

inline uint16       mygis_swap_uint16(uint16 in);
inline uint32       mygis_swap_uint32(uint32 in);
inline uint64       mygis_swap_uint64(uint64 in);
inline float        mygis_swap_float(float in);
inline double       mygis_swap_double(double in);
char                *mygis_trim(char *str, uint32 len);

#endif /* MYGIS_H */
