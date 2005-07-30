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

#include "mygis.h"
#include "pairlist.h"
#include <stdlib.h>
#include <string.h>

PAIR *pair_set(PAIR *pair, char *key, char *value)
{
  DBUG_ENTER("pair_set");
  DBUG_PRINT("args", ("pair=0x%08x key=%s value=%s", pair, key, value));

  pair->key   = (char *)realloc(pair->key,   strlen(key)  +1);
  pair->value = (char *)realloc(pair->value, strlen(value)+1);

  strcpy(pair->key,   key);
  strcpy(pair->value, value);

  DBUG_RETURN(pair);
}

PAIRLIST *pairlist_init(COMPARE *compare_key, COMPARE *compare_value)
{
  PAIRLIST *list;

  DBUG_ENTER("pairlist_init");
  if(!(list = PAIRLIST_INIT)) {
    DBUG_RETURN(NULL);
  }

  list->compare_key   = compare_key;
  list->compare_value = compare_value;
  list->root = NULL;
  list->pairs = 0;
  
  DBUG_RETURN(list);
}

PAIRNODE *pairlist_add(PAIRLIST *list, char *key, char *value)
{
  PAIRNODE *node;

  DBUG_ENTER("pairlist_add");

  if(!(node = PAIRNODE_INIT))
    DBUG_RETURN(NULL);
  node->pair.key = NULL;
  node->pair.value = NULL;

  pair_set(&node->pair, key, value);

  node->prev = NULL;
  node->next = list->root;
  if(list->root) list->root->prev = node;
  list->root = node;

  list->pairs++;

  DBUG_RETURN(node);
}

PAIRNODE *pairlist_get(PAIRLIST *list, char *key)
{
  PAIRNODE *cur = list->root;

  DBUG_ENTER("pairlist_get");

  if(!cur) DBUG_RETURN(NULL);

  for(; cur; cur=cur->next) {
    if(list->compare_key->func(cur->pair.key, key)) {
      DBUG_RETURN(cur);
    }
  }

  DBUG_RETURN(NULL);
}

char *pairlist_get_value(PAIRLIST *list, char *key)
{
  PAIRNODE *node;

  DBUG_ENTER("pairlist_get_value");
  if((node = pairlist_get(list, key))) {
    DBUG_RETURN(node->pair.value);
  }
  DBUG_RETURN(NULL);
}

void pairlist_remove_node(PAIRLIST *list, PAIRNODE *node)
{
  DBUG_ENTER("pairlist_remove");
  if(!node) DBUG_VOID_RETURN;
  if(node->next) node->next->prev = node->prev;
  if(node->prev) node->prev->next = node->next;
  free(node->pair.key);
  free(node->pair.value);
  free(node);
  list->pairs--;
  DBUG_VOID_RETURN;
}

void pairlist_remove(PAIRLIST *list, char *key)
{
  DBUG_ENTER("pairlist_remove");
  pairlist_remove_node(list, pairlist_get(list, key));
  DBUG_VOID_RETURN;
}

void pairlist_dump(PAIRLIST *list)
{
  PAIRNODE *cur = list->root;

  DBUG_ENTER("pairlist_dump");

  for(; cur; cur=cur->next) {
    printf("Node 0x%08x: <%s> = <%s>\n", (unsigned int)cur, cur->pair.key, cur->pair.value);
  }

  DBUG_VOID_RETURN;
}

void pairlist_free(PAIRLIST *list)
{
  PAIRNODE *cur = list->root;

  DBUG_ENTER("pairlist_free");

  for(; cur; cur=cur->next) {
    free(cur->pair.key);
    free(cur->pair.value);
    if(cur->next) cur->next->prev = NULL;
    free(cur);
  }

  DBUG_VOID_RETURN;
}
