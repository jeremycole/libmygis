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

#include <string.h>

#include "compare.h"

int compare_all_func(void *a, void *b) {
  DBUG_ENTER("compare_all_func");
  DBUG_PRINT("info", ("Always returns true"));
  DBUG_RETURN(1);
}

int compare_string_cs_eq_func(void *a, void *b) {
  DBUG_ENTER("compare_string_cs_eq_func");
  DBUG_PRINT("args", ("a=%s b=%s", (char *)a, (char *)b));
  DBUG_RETURN((strcmp((char *)a, (char *)b)==0));
}

int compare_string_cs_ne_func(void *a, void *b) {
  DBUG_ENTER("compare_string_ci_eq_func");
  DBUG_PRINT("args", ("a=%s b=%s", (char *)a, (char *)b));
  DBUG_RETURN((strcmp((char *)a, (char *)b)!=0));
}
  
int compare_string_ci_eq_func(void *a, void *b) {
  DBUG_ENTER("compare_string_ci_eq_func");
  DBUG_PRINT("args", ("a=%s b=%s", (char *)a, (char *)b));
  DBUG_RETURN((strcasecmp((char *)a, (char *)b)==0));
}

int compare_string_ci_ne_func(void *a, void *b) {
  DBUG_ENTER("compare_string_ci_ne_func");
  DBUG_PRINT("args", ("a=%s b=%s", (char *)a, (char *)b));
  DBUG_RETURN((strcasecmp((char *)a, (char *)b)!=0));
}

COMPARE compare_all = {
  "Match All",
  "*", compare_all_func
};

COMPARE compare_string_cs_eq = {
  "String, Case-Sensitive, Equal",
  "==", compare_string_cs_eq_func
};

COMPARE compare_string_cs_ne = {
  "String, Case-Sensitive, Not Equal",
  "!=", compare_string_cs_ne_func
};

COMPARE compare_string_ci_eq = {
  "String, Case-Insensitive, Equal",
  "==", compare_string_ci_eq_func
};

COMPARE compare_string_ci_ne = {
  "String, Case-Insensitive, Not Equal",
  "!=", compare_string_ci_ne_func
};
