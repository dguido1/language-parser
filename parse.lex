%{
#include "parse.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

%%

[0-9]+(\.[0-9]+)?([eE][0-9]+)?  {yylval.f = atof(yytext); return }

[-+()*/]                        {return yytext[0];}

[\t\f\v\n]                      {;}

%%
