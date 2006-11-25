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
#include "projection.h"
#include <stdlib.h>
#include <string.h>

PROJECTION *projection_init()
{
  PROJECTION *proj;

  DBUG_ENTER("projection_init");
  if(!(proj = PROJECTION_INIT))
  {
    DBUG_RETURN(NULL);
  }
  
  projection_unset(proj);

  DBUG_RETURN(proj);
}

int projection_set(PROJECTION *proj, char *from, char *to)
{
  DBUG_ENTER("projection_set");

  projection_unset(proj);

  proj->from      = strdup(from);
  proj->to        = strdup(to);

  if(!(proj->proj4_pj_from = pj_init_plus(proj->from)))
    goto err5;

  if(!(proj->proj4_pj_to   = pj_init_plus(proj->to)))
    goto err6;

  proj->is_set = 1;

  DBUG_RETURN(0);

 err6:
  pj_free(proj->proj4_pj_to);
 err5:
  pj_free(proj->proj4_pj_from);
 err4:
  free(proj->to);
 err2:
  free(proj->from);
 err:
  DBUG_RETURN(-1);
}

void projection_unset(PROJECTION *proj)
{
  DBUG_ENTER("projection_unset");

  if(!proj->is_set)
  {
    pj_free(proj->proj4_pj_to);
    pj_free(proj->proj4_pj_from);
    free(proj->to);
    free(proj->to_name);
    free(proj->from);
    free(proj->from_name);
  }
  
  proj->from_name = NULL;
  proj->from      = NULL;
  proj->to_name   = NULL;
  proj->to        = NULL;
  
  proj->proj4_pj_from = NULL;
  proj->proj4_pj_to   = NULL;

  proj->is_set    = 0;

  DBUG_VOID_RETURN;
}

POINT *projection_transform(PROJECTION *proj, POINT *point)
{
  double trash_z = 0.0;
  POINT *ret = point;
  int rc;

  DBUG_ENTER("projection_transform");
  if(!proj->is_set) 
    goto err;

  rc= pj_transform(proj->proj4_pj_from, proj->proj4_pj_to,
                   1, 0, &ret->x, &ret->y, &trash_z);

  if(rc)
    DBUG_RETURN(NULL);

 err:
  DBUG_RETURN(ret);
}

void projection_dump(PROJECTION *proj)
{
  DBUG_ENTER("projection_dump");
  printf("PROJECTION: Dump: 0x%08x\n", (int)proj);
  printf("  Structure:\n");
  printf("    from_name:      %s\n", proj->from_name);
  printf("    from:           %s\n", proj->from);
  printf("    proj4_pj_from:  0x%08x\n", (int)proj->proj4_pj_from);
  printf("    to_name:        %s\n", proj->to_name);
  printf("    to:             %s\n", proj->to);
  printf("    proj4_pj_to:    0x%08x\n", (int)proj->proj4_pj_to);  
  printf("\n\n");
  DBUG_VOID_RETURN;
}

void projection_free(PROJECTION *proj)
{
  DBUG_ENTER("projection_free");
  projection_unset(proj);
  free(proj);
  DBUG_VOID_RETURN;
}



