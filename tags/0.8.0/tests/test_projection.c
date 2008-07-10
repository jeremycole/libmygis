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

#include <stdio.h>

#include "mygis.h"
#include "projection.h"

#ifndef HAVE_PROJECTION

int main(int argc, char **argv)
{
  return 0;
}

#else /* HAVE_PROJECTION */

int main(int argc, char **argv) {
  PAIRLIST *args;
  PROJECTION *proj;
  POINT a, b;

  DBUG_PUSH("d:t");

  if(!(args = pairlist_init(&compare_string_ci_eq, &compare_string_ci_eq))) {
    fprintf(stderr, "Couldn't init pairlist for args\n");
    return 1;
  }

  if(!(proj = projection_init()))
  {
    fprintf(stderr, "Couldn't init projection\n");
    return 1;
  }

  /*
  pairlist_add(args, "from_name",
                     "NAD_1983_StatePlane_Nevada_West_FIPS_2703_Feet");
  pairlist_add(args, "from", "+proj=tmerc +ellps=GRS80 +datum=NAD83 +k=0.9999 +units=us-ft +x_0=2624666.666666 +y_0=13123333.333333 +lon_0=-118.583333 +lat_0=+34.75");
  
  // washoe/wcroads.* loc: 39.430183,-119.742816
  // seems broken
  a.x = 2297190.783459;
  a.y = 14829485.209469;
  */

  /*
  pairlist_add(args, "from_name",
                     "NAD_1983_StatePlane_Massachusetts_Mainland_FIPS_2001");
  pairlist_add(args, "from", "+proj=lcc +datum=NAD83 +x_0=200000.0 +y_0=750000.0 +lon_0=-71.5 +lat_0=41.0 +lat_1=41.71666666666667 +lat_2=42.68333333333333 +units=m");

  // mbta/biketrails_arc.*
  // might be good
  a.x = 219639.029997;
  a.y = 897894.252106;
  */
  
  //pairlist_add(args, "from", "+proj=utm +zone=11 +datum=NAD83 +units=m");
  pairlist_add(args, "from", "+proj=tmerc +datum=NAD83 +units=m +lat_0=0.0000000000 +k=0.9996000000 +lon_0=-117.0000000000 +y_0=0.0000000000 +x_0=500000.0000000000");
  
  // nvblm/nv_fires_20061010.*
  // looks good
  a.x = 243219.221279;
  a.y = 4380953.713629;
  
  pairlist_add(args, "to", "+proj=latlong +towgs84");

  pairlist_dump(args);

  projection_set(proj,
                 pairlist_get_value(args, "from"),
                 pairlist_get_value(args, "to"));
  
  printf("x= %0.6f, y=%0.6f\n", a.x, a.y);

  b = *(projection_transform(proj, &a));
  
  printf("loc:%0.6f,%0.6f\n", a.y*RAD_TO_DEG, a.x*RAD_TO_DEG);

  pairlist_free(args);

  return 0;
}

#endif /* !HAVE_PROJECTION */
