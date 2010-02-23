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

#ifndef PAIRLIST_H
#define PAIRLIST_H

#include "compare.h"

typedef struct pair_st {
  char *key;
  char *value;
} PAIR;

typedef struct pairnode_st {
  PAIR pair;
  struct pairnode_st *prev;
  struct pairnode_st *next;
} PAIRNODE;  

typedef struct pairlist_st {
  COMPARE *compare_key, *compare_value;
  PAIRNODE *root;
  int pairs;
} PAIRLIST;

PAIR *pair_set(PAIR *pair, char *key, char *value);

PAIRLIST *pairlist_init(COMPARE *compare_key, COMPARE *compare_value);
PAIRNODE *pairlist_add(PAIRLIST *list, char *key, char *value);
PAIRNODE *pairlist_get(PAIRLIST *list, char *key);
char *pairlist_get_value(PAIRLIST *list, char *key);
void pairlist_remove_node(PAIRLIST *list, PAIRNODE *node);
void pairlist_remove(PAIRLIST *list, char *key);
void pairlist_dump(PAIRLIST *list);
void pairlist_free(PAIRLIST *list);

#endif /* PAIRLIST_H */
