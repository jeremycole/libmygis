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

#include "wkb_priv.h"

const char WKB_TYPES[8][20] = {
  {"UNKNOWN"},
  {"POINT"},
  {"LINESTRING"},
  {"POLYGON"},
  {"MULTIPOINT"},
  {"MULTILINESTRING"},
  {"MULTIPOLYGON"},
  {"GEOMETRYCOLLECTION"}
};

WKB *wkb_init(int flags)
{
  WKB *wkb;

  DBUG_ENTER("wkb_init");

  if(!(wkb = WKB_INIT) )
    DBUG_RETURN(NULL);

  wkb->mydata = NULL;  wkb->mydata_len = 0;
  wkb->data = NULL;    wkb->data_len = 0;
  wkb->next = NULL;

  DBUG_RETURN(wkb);
}

int wkb_load(WKB *wkb, char *data, unsigned int data_len, int flags)
{
  DBUG_ENTER("wkb_load");

  if(flags & WKB_F_DUPE)
  {
    if((data_len < wkb->mydata_len) ||
       (wkb->mydata = wkb->data = (char *)realloc((void *)wkb->mydata, wkb->mydata_len=data_len)) )
    {
      memcpy(wkb->data, data, data_len);
    } else {
      DBUG_RETURN(1);
    }
  } else {
    wkb->data = data;
  }
  wkb->data_len = data_len;
  wkb->flags = flags;
  wkb_rewind(wkb);

  DBUG_RETURN(0);
}

void wkb_rewind(WKB *wkb)
{
  DBUG_ENTER("wkb_rewind");

  if(wkb)
  {
    wkb->cur  = wkb->data;
    wkb->next = NULL;
  }

  DBUG_VOID_RETURN;
}

void wkb_free(WKB *wkb)
{
  DBUG_ENTER("wkb_free");

  if(!wkb) DBUG_VOID_RETURN;
  if(wkb->flags & WKB_F_DUPE) free(wkb->mydata);
  free(wkb);

  DBUG_VOID_RETURN;
}

