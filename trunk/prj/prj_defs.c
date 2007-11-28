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

#include "prj_priv.h"
#include "prj_defs.h"

PRJ_PROJ4_NAMES prj_proj4_geogcs_names[] =
{
  { "GCS_North_American_1983", "" },
  { NULL, NULL }
};

PRJ_PROJ4_NAMES prj_proj4_datum_names[] =
{
  { "D_North_American_1983", "NAD83" },
  { NULL, NULL }
};

PRJ_PROJ4_NAMES prj_proj4_spheroid_names[] =
{
  { "GRS_1980", "grs80" },
  { NULL, NULL }
};

PRJ_PROJ4_NAMES prj_proj4_projection_names[] =
{
  { "Transverse_Mercator", "tmerc" },
  { "Lambert_Conformal_Conic", "lcc" },
  { "Albers", "aea" },
  { NULL, NULL }
};

PRJ_PROJ4_NAMES prj_proj4_unit_names[] =
{
  { "Meter", "m" },
  { "Foot_US", "us-ft" },
  { NULL, NULL }
};

PRJ_PROJ4_NAMES prj_proj4_parameter_names[] =
{
  { "False_Easting",        "x_0"   },
  { "False_Northing",       "y_0"   },
  { "Central_Meridian",     "lon_0" },
  { "Latitude_Of_Origin",   "lat_0" },
  { "Standard_Parallel_1",  "lat_1" },
  { "Standard_Parallel_2",  "lat_2" },
  { "Scale_Factor",         "k"     },
  { NULL, NULL }
};

char *prj_proj4_names_find(PRJ_PROJ4_NAMES *names, char *name)
{
  PRJ_PROJ4_NAMES *cur = names;
  
  DBUG_ENTER("prj_proj4_names_find");
  for(; cur; cur++)
  {
    if(!cur->prj_name)
      DBUG_RETURN(NULL);
    if(!strcmp(cur->prj_name, name))
      DBUG_RETURN(cur->proj4_name);
  }
  
  DBUG_RETURN(NULL);
}
