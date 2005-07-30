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

#include <string.h>

#include "mygis.h"

#ifdef DEBUG
#define DEBUG_STRING " (debug)"
#else
#define DEBUG_STRING ""
#endif

const char *mygis_version   = { "libmygis " VERSION DEBUG_STRING };
const char *mygis_copyright = { "Copyright (c) 2004-2005, Jeremy Cole." };
const char *mygis_license   = { "LGPL - Lesser (Library) General Public License" };

inline uint16 mygis_swap_uint16(uint16 in) {
  MYGIS_SWAP_UINT16(&in);
  return(in);
}

inline uint32 mygis_swap_uint32(uint32 in) {
  MYGIS_SWAP_UINT32(&in);
  return(in);
}

inline uint64 mygis_swap_uint64(uint64 in) {
  MYGIS_SWAP_UINT64(&in);
  return(in);
}

inline float mygis_swap_float(float in) {
  MYGIS_SWAP_FLOAT(&in);
  return(in);
}

inline double mygis_swap_double(double in) {
  MYGIS_SWAP_DOUBLE(&in);
  return(in);
}

char *mygis_trim(char *str, uint32 len) {
  char *p = str+len-1;

  for(;p > str;p--) {
    if(*p == ' ') {
      *p = '\0';
    } else return str;
  }

  return str;
}
