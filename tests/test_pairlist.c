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

#include "mygis_priv.h"
#include "pairlist_priv.h"

int main(int argc, char **argv)
{
  PAIRLIST *list;

  DBUG_PUSH("d:t");

  if(!(list = pairlist_init(&compare_string_ci_eq, &compare_string_ci_eq)))
  {
    fprintf(stderr, "Couldn't init pairlist\n");
    return 1;
  }

  pairlist_add(list, "name", "Jeremy Cole");
  pairlist_add(list, "age", "23");
  pairlist_add(list, "height", "6'1\"");

  printf("name=%s age=%s height=%s\n",
	 pairlist_get_value(list, "name"),
	 pairlist_get_value(list, "age"),
	 pairlist_get_value(list, "height"));

  pairlist_dump(list);

  pairlist_free(list);

  return 0;
}
