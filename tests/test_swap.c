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

#include "mygis_priv.h"

int main(int argc, char **argv) {
  uint16 s, ss;
  uint32 u, uu;
  double d, dd;

  ss = s = 1234;
  uu = u = 132234234;
  dd = d = 1234.1234;

  printf("\nOriginal values:\n");
  printf("  s = %12hi\n", s);
  printf("  u = %12i\n", u);
  printf("  d = %12f\n", d);

  MYGIS_SWAP_UINT16(&s);
  MYGIS_SWAP_UINT32(&u);
  MYGIS_SWAP_DOUBLE(&d);

  printf("\nSwapped once:\n");
  printf("  s = %12hi\n", s);
  printf("  u = %12i\n", u);
  printf("  d = %12f\n", d);

  MYGIS_SWAP_UINT16(&s);
  MYGIS_SWAP_UINT32(&u);
  MYGIS_SWAP_DOUBLE(&d);

  printf("\nSwapped twice:\n");
  printf("  s = %12hi\n", s);
  printf("  u = %12i\n", u);
  printf("  d = %12f\n", d);

  if(ss == s && uu == u && dd == d) {
    printf("\n\nAll values matched!  Everything seems to have worked OK!\n\n");
  } else {
    printf("\n\nSomething went wrong!!!\n\n");
  }

  return 0;
}
