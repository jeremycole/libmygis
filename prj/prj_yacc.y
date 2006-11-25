%{
#define YYINCLUDED 1

#include <stdio.h>
#include <string.h>
#include "../mygis.h"
#include "prj.h"

extern char* yytext;
extern int yylineno;
extern FILE* yyin;
int yyparse();
int yylex();

PRJ_PROJCS *projcs;
PRJ_KV *unit;

char tmpbuf[4096];

#ifndef DBUG_OFF
#define YYDEBUG 1
int yydebug = 1;
#endif

void yyerror(char *);
%}

%token  P_OB_SYM
%token  P_CB_SYM
%token  P_COMMA_SYM

%token  STRING_SYM
%token  REAL_SYM

%token  PROJCS_SYM
%token  GEOGCS_SYM
%token  DATUM_SYM
%token  SPHEROID_SYM
%token  PRIMEM_SYM
%token  UNIT_SYM
%token  PROJECTION_SYM
%token  PARAMETER_SYM

%union
{
  char str[4096];
  double real;
}

%type <str> STRING_SYM
%type <real> REAL_SYM

%start prj_file

%%

prj_file:
  projcs_def
  ;
  
projcs_def:
  PROJCS_SYM
  P_OB_SYM 
    STRING_SYM P_COMMA_SYM 
    projcs_body
  P_CB_SYM
  {
    strcpy(projcs->name, $3);
  }
  ;

projcs_body:
  projcs_body_part
  | projcs_body_part P_COMMA_SYM projcs_body
  ;

projcs_body_part:
  /* empty */
  | geogcs_def
  | projection_def 
  | parameter_def
  | unit_def
  ;

geogcs_def:
  GEOGCS_SYM
  P_OB_SYM
    { unit = &projcs->geogcs.unit; }
    STRING_SYM P_COMMA_SYM
    geogcs_body
    { unit = &projcs->unit; }
  P_CB_SYM
  {
    strcpy(projcs->geogcs.name, $4);
  }
  ;
  
geogcs_body:
  geogcs_body_part
  | geogcs_body_part P_COMMA_SYM geogcs_body
  ;
  
geogcs_body_part:
  /* empty */
  | datum_def
  | primem_def
  | unit_def
  ;

datum_def:
  DATUM_SYM
  P_OB_SYM
    STRING_SYM P_COMMA_SYM
    spheroid_def
  P_CB_SYM
  {
    strcpy(projcs->geogcs.datum.name, $3);
  }
  ;

spheroid_def:
  SPHEROID_SYM 
  P_OB_SYM 
    STRING_SYM P_COMMA_SYM 
    REAL_SYM P_COMMA_SYM 
    REAL_SYM 
  P_CB_SYM
  {
    strcpy(projcs->geogcs.datum.spheroid.name, $3);
    projcs->geogcs.datum.spheroid.value1 = $5;
    projcs->geogcs.datum.spheroid.value2 = $7;
  }
  ;

primem_def:
  PRIMEM_SYM 
  P_OB_SYM 
    STRING_SYM P_COMMA_SYM 
    REAL_SYM 
  P_CB_SYM
  {
    strcpy(projcs->geogcs.primem.name, $3);
    projcs->geogcs.primem.value = $5;
  }
  ;

unit_def:
  UNIT_SYM
  P_OB_SYM
    STRING_SYM P_COMMA_SYM
    REAL_SYM
  P_CB_SYM
  {
    strcpy(unit->name, $3);
    unit->value = $5;
  }
  ;

projection_def:
  PROJECTION_SYM
  P_OB_SYM
    STRING_SYM
  P_CB_SYM
  {
    strcpy(projcs->projection, $3);
  }
  ;

parameter_def:
  PARAMETER_SYM
  P_OB_SYM
    STRING_SYM P_COMMA_SYM
    REAL_SYM
  P_CB_SYM
  {
    sprintf(tmpbuf, "%0.10f", $5);
    pairlist_add(projcs->parameters, $3, tmpbuf);
  }
  ;
  
%%

void yyerror(char* msg)
{
  fprintf(stderr, "Parse error on line %d near %s\n", yylineno, yytext);
  exit(1);
}

void prj_parse_yacc(PRJ *prj, char *prjfile)
{
  FILE *f;
  f = fopen(prjfile, "r");
  
  projcs = &prj->projcs;
  yyin = f;
  yyparse();
  projcs->is_filled = 1;

  fclose(f);
}
