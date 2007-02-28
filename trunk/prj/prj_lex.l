%{

#include <string.h>
#include "prj_yacc_stub.h"

static char q_str[4096];

%}

%option yylineno

%x Q_STR

WHITE	[ \n\t]
LETTER	[a-zA-Z]
IDENT_CHAR [a-zA-Z0-9_]
DIGIT [0-9\.\-\+]

%%

<INITIAL>"["          { return P_OB_SYM;       }
<INITIAL>"]"          { return P_CB_SYM;       }
<INITIAL>","          { return P_COMMA_SYM;    }

<INITIAL>"PROJCS"     { return PROJCS_SYM;     }
<INITIAL>"GEOGCS"     { return GEOGCS_SYM;     }
<INITIAL>"DATUM"      { return DATUM_SYM;      }
<INITIAL>"SPHEROID"   { return SPHEROID_SYM;   }
<INITIAL>"PRIMEM"     { return PRIMEM_SYM;     }
<INITIAL>"UNIT"       { return UNIT_SYM;       }
<INITIAL>"PROJECTION" { return PROJECTION_SYM; }
<INITIAL>"PARAMETER"  { return PARAMETER_SYM;  }

<INITIAL>{DIGIT}+ {
  yylval.real = atof(yytext);
  return REAL_SYM;
}

<INITIAL>"\"" { 
  BEGIN Q_STR;
  q_str[0] = 0;
}
<Q_STR>"\"" {
  BEGIN 0;
  strcpy(yylval.str, q_str);
  return STRING_SYM;
}
<Q_STR>.|\n { strcat(q_str, yytext); }

.|\n {}

%%

int yywrap(void)
{
  return 1;
}

