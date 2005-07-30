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

#include "config.h"
#include "portability.h"

#ifndef HAVE_STRNDUP
char *strndup(const char *s, size_t n)
{
  char *tmp;
  if(!(tmp = (char *)malloc(n+1))) return NULL;
  strncpy(tmp, s, n);
  tmp[n] = '\0';
  return tmp;
}
#endif /* HAVE_STRNDUP */


#ifndef HAVE_GETLINE
ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
}
#endif /* HAVE_GETLINE */
