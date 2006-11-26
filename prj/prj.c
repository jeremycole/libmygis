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

#include "mygis.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "prj.h"
#include "prj_defs.h"

PRJ *prj_init(int flags)
{
  PRJ *prj;
  
  DBUG_ENTER("prj_init");
  
  if(!(prj = PRJ_INIT))
  {
    DBUG_RETURN(NULL);
  }
  
  if(!(prj->projcs.parameters = pairlist_init(&compare_string_ci_eq,
                                              &compare_string_ci_eq)))
  {
    free(prj);
    DBUG_RETURN(NULL);
  }
    
  prj->filename = NULL;
  prj->proj4_def[0] = 0;

  DBUG_RETURN(prj);
}

int prj_parse(PRJ *prj, char *prjfile)
{
  int fd;
  off_t size;
  char *name;
  PAIRNODE *param;

  DBUG_ENTER("prj_parse");

  prj->filename = strdup(prjfile);
  
  if((fd = open(prjfile, O_RDONLY)) < 0)
  {
    fprintf(stderr, "Error opening PRJ file: %i: %s\n", 
      errno, strerror(errno));
    DBUG_RETURN(-1);
  }

  size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  
  if(!(prj->definition = malloc(size)))
  {
    fprintf(stderr, "Couldn't allocate %i bytes\n", size);
    DBUG_RETURN(-2);
  }

  if(read(fd, prj->definition, size) != size)
  {
    fprintf(stderr, "Didn't read entire file\n");
    DBUG_RETURN(-3);
  }
  
  if(strncmp(prj->definition, "PROJCS", 6) != 0)
  {
    fprintf(stderr, "Doesn't look like a real PRJ file; doesn't start with PROJCS");
    DBUG_RETURN(-4);
  }

  prj_parse_yacc(prj, prjfile);

  name= prj_proj4_names_find(prj_proj4_projection_names,
                             prj->projcs.projection);
  if(name)
  {
    strcat(prj->proj4_def, " +proj=");
    strcat(prj->proj4_def, name);
  }

  name= prj_proj4_names_find(prj_proj4_datum_names,
                             prj->projcs.geogcs.datum.name);
  if(name)
  {
    strcat(prj->proj4_def, " +datum=");
    strcat(prj->proj4_def, name);
  }

  name= prj_proj4_names_find(prj_proj4_unit_names,
                             prj->projcs.unit.name);
  if(name)
  {
    strcat(prj->proj4_def, " +units=");
    strcat(prj->proj4_def, name);
  }

  for(param = prj->projcs.parameters->root; param; param=param->next) {
    name= prj_proj4_names_find(prj_proj4_parameter_names,
                               param->pair.key);
    strcat(prj->proj4_def, " +");
    strcat(prj->proj4_def, name);
    strcat(prj->proj4_def, "=");
    strcat(prj->proj4_def, param->pair.value);
  }

  close(fd);
  
  DBUG_RETURN(0);
}

void prj_dump(PRJ *prj)
{
  DBUG_ENTER("prj_dump");

  PAIRNODE *param = prj->projcs.parameters->root;

  printf("\n");
  printf("PRJ: Dump: 0x%08x\n", (int)prj);
  printf("  Structure:\n");

  if(prj->projcs.is_filled)
  {
    printf("    projcs: %s\n", prj->projcs.name);
    printf("      proj4_def: %s\n", prj->proj4_def);
    printf("      geogcs: %s\n", prj->projcs.geogcs.name);
    printf("        datum: %s\n", prj->projcs.geogcs.datum.name);
    printf("          spheroid: %s (%0.6f, %0.6f)\n",
      prj->projcs.geogcs.datum.spheroid.name,
      prj->projcs.geogcs.datum.spheroid.value1,
      prj->projcs.geogcs.datum.spheroid.value2);
    printf("        primem: %s (%0.6f)\n",
      prj->projcs.geogcs.primem.name, prj->projcs.geogcs.primem.value);
    printf("        unit: %s (%0.6f)\n",
      prj->projcs.geogcs.unit.name, prj->projcs.geogcs.unit.value);
    printf("      projection: %s\n", prj->projcs.projection);
    printf("      unit: %s (%0.6f)\n",
      prj->projcs.unit.name, prj->projcs.unit.value);
    printf("      parameters:\n");
  
    if(!param)
    {
      printf("        (none)\n");
    }
  
    for(; param; param=param->next) {
      printf("        %-20s = %20s\n",
        param->pair.key, param->pair.value);
    }
  } else {
    printf("    (not filled)\n");
  }

  printf("\n\n");
  
  DBUG_VOID_RETURN;
}

void prj_free(PRJ *prj)
{
  pairlist_free(prj->projcs.parameters);
  free(prj);
}
