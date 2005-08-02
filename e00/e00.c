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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "geometry.h"

#include "e00.h"
#include "e00_priv.h"

E00_SECTION_TAG E00_SECTION_TAGS[E00_SECTION_IDS+1] = {
  {"UNKNOWN", UNKNOWN},
  {"ARC", ARC},
  {"CNT", CNT},
  {"LAB", LAB},
  {"PAL", PAL},
  {"PAR", PAR},
  {"TOL", TOL},
  {"TXT", TXT},
  {"TX6", TX6},
  {"TX7", TX7},
  {"IFO", IFO},
  {"RXP", RXP},
  {"RPL", RPL},
  {"LOG", LOG},
  {"PRJ", PRJ},
  {"SIN", SIN},
  {0, 0}
};

E00 *e00_init(int flags)
{
  E00 *e00;

  DBUG_ENTER("e00_init");

  if(!(e00 = E00_INIT)) {
    DBUG_RETURN(NULL);
  }

  e00->fd       = 0;
  e00->filename = NULL;
  e00->mode     = '\0';
  e00->position = 0;
  e00->records  = 0;

  DBUG_RETURN(e00);
}

int e00_open(E00 *e00, char *e00file, char mode)
{
  DBUG_ENTER("e00_open");
  DBUG_PRINT("info", ("E00: Opening '%s', mode '%c'", e00file, mode));

  e00->mode     = mode;
  e00->filename = strdup(e00file);

  switch(mode) {
  case 'r':
    if((e00->fd = open(e00file, O_RDONLY)) < 0) {
      fprintf(stderr, "E00: Error opening `%s' for read: Error %i: %s\n",
	      e00file, errno, strerror(errno));
      DBUG_RETURN(-1);
    }
    e00_rewind(e00);

    e00->sections.arc = e00_open_section(e00, "ARC");
    e00->sections.lab = e00_open_section(e00, "LAB");

    break;

  case 'w':
    DBUG_RETURN(-1);
    break;

  default:
    fprintf(stderr, "E00: Unknown mode '%c'\n", mode);
    DBUG_RETURN(-255);
  }

  DBUG_RETURN(e00->fd);
}

E00_SECTION_ID e00_section_id(char *section_tag)
{
  E00_SECTION_TAG *t = E00_SECTION_TAGS;
  for(; t->tag; t++) {
    if((strcmp(section_tag, t->tag)) == 0)
      return t->id;
  }
  return UNKNOWN;
}


E00_SECTION *e00_open_section(E00 *e00, char *section_tag)
{
  E00_SECTION *section;

  char current_tag[5];
  int current_prec;
  E00_SECTION_ID current_id;

  int int_tmp;
  char str_tmp[15];

  char *line = NULL;
  ssize_t len = 0;
  ssize_t read;

  char *line2 = NULL;
  ssize_t len2 = 0;
  ssize_t read2;

  DBUG_ENTER("e00_open_section");
  DBUG_PRINT("info", ("Opening `%s' section", section_tag));

  if(!(section = E00_SECTION_INIT)) {
    goto err1;
  }

  section->id = e00_section_id(section_tag);  

  if((section->fd = open(e00->filename, O_RDONLY)) < 0) {
    fprintf(stderr, "E00: Error opening `%s' for read of section `%s': Error %i: %s\n",
	    e00->filename, section_tag, errno, strerror(errno));
    goto err2;
  }

  section->file = fdopen(section->fd, "r");
  read = getline(&line, &len, section->file);

  while(!feof(section->file)) {
    read = getline(&line, &len, section->file);
    sscanf(line, "%3s %i", current_tag, &current_prec);

    if((strcmp(current_tag, "EOS") == 0)) goto no_section;

    if((current_id = e00_section_id(current_tag)) == section->id) {
      DBUG_PRINT("info", ("Found `%s' section with precision %i",
			  current_tag, current_prec));
      fgetpos(section->file, &section->start_pos);
      section->precision = current_prec;
      DBUG_RETURN(section);
    }

    /* Skip over rest of section... */
    DBUG_PRINT("info", ("Skipping over `%s' section", current_tag));
    switch(current_id) {

    case ARC:
    case CNT:
    case PAL:
    case TOL:
    case TXT:
      int_tmp = 0;
      while((!feof(section->file)) && (int_tmp != -1)) {
	read = getline(&line, &len, section->file);
	sscanf(line, " %i %*s\n", &int_tmp);
      }
      break;

    case TX6:
    case TX7:
    case RXP:
    case RPL:
      strcpy(str_tmp, "");
      while((!feof(section->file)) && (strcmp(str_tmp, "JABBERWOCKY") != 0)) {
	read = getline(&line, &len, section->file);
	sscanf(line, "%11s %*s", str_tmp);
      }
      break;

    case LAB:
      int_tmp = 0;
      while((!feof(section->file)) && (int_tmp != -1)) {
	read = getline(&line, &len, section->file);
	sscanf(line, " %i %*s\n", &int_tmp);
	if(int_tmp != -1) read2 = getline(&line2, &len2, section->file);
      }
      break;

    case IFO:
      strcpy(str_tmp, "");
      while((!feof(section->file)) && (strcmp(str_tmp, "EOI") != 0)) {
	read = getline(&line, &len, section->file);
	sscanf(line, "%3s %*s", str_tmp);
      }
      break;

    case LOG:
      strcpy(str_tmp, "");
      while((!feof(section->file)) && (strcmp(str_tmp, "EOL") != 0)) {
	read = getline(&line, &len, section->file);
	sscanf(line, "%3s %*s", str_tmp);
      }
      break;

    case PRJ:
      strcpy(str_tmp, "");
      while((!feof(section->file)) && (strcmp(str_tmp, "EOP") != 0)) {
	read = getline(&line, &len, section->file);
	sscanf(line, "%3s %*s", str_tmp);
      }
      break;

    case SIN:
      strcpy(str_tmp, "");
      while((!feof(section->file)) && (strcmp(str_tmp, "EOX") != 0)) {
	read = getline(&line, &len, section->file);
	sscanf(line, "%3s %*s", str_tmp);
      }
      break;

    case UNKNOWN:
    default:
      DBUG_PRINT("error", ("Unknown section type found, can't skip!"));
      DBUG_PRINT("info", ("line=`%s'", line));
      break;
    }
  }

 no_section:
  DBUG_PRINT("info", ("No `%s' section in file", section_tag));
 err3:
  fclose(section->file);
 err2:
  free(section);
 err1:
  DBUG_RETURN(NULL);
}


void e00_seek(E00 *e00, int pos)
{
  DBUG_ENTER("e00_seek");
  DBUG_PRINT("info", ("E00: Seeking to offset %i", pos));
  lseek(e00->fd, pos, SEEK_SET);
  DBUG_VOID_RETURN;
}

void e00_record_seek(E00 *e00, uint32 record)
{
  DBUG_ENTER("e00_record_seek");
  DBUG_PRINT("info", ("E00: Record seeking to record %i", record));

  DBUG_VOID_RETURN;
}

void e00_rewind(E00 *e00)
{
  DBUG_ENTER("e00_rewind");
  e00_record_seek(e00, 0);
  DBUG_VOID_RETURN;
}

void e00_dump(E00 *e00)
{
  DBUG_ENTER("e00_dump");
  printf("\n");
  printf("E00: Dump: 0x%08x\n", (int)e00);
  printf("  Structure:\n");
  printf("    filename:   %s\n", e00->filename);
  printf("    fd:         %i\n", e00->fd);
  printf("    mode:       %c\n", e00->mode);
  printf("    flags:      %i\n", e00->flags);
  printf("    position:   %i\n", e00->position);
  printf("    records:    %i\n", e00->records);
  printf("\n\n");
  DBUG_VOID_RETURN;
}

void e00_close(E00 *e00)
{
  DBUG_ENTER("e00_close");
  if(e00->fd) {
    close(e00->fd);
  }
  DBUG_VOID_RETURN;
}

void e00_free(E00 *e00)
{
  DBUG_ENTER("e00_free");
  if(e00) {
    if(e00->filename) free(e00->filename);
    free(e00);
  }
  DBUG_VOID_RETURN;
}

