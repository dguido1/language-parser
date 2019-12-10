%{
#include "parse.tab.h"
#include <stdio.h>
#include <string.h>
%}

%option noyywrap

number      ([0-9])+

%%
"PROGRAM"       {   return(PROGRAM);    }
"VAR"           {   return(VAR);        }
"BEGIN"         {   return(START);      }
"END"           {   return(END);        }
"INTEGER"       {   return(INTEGER);    }
"PRINT"         {   return(PRINT);      }
{number}        {   return(NUM);        }
"."             {   return(PERIOD);     }
":"             {   return(COLON);      }
";"             {   return(SEMICOLON);  }
","             {   return(COMMA);      }
"("             {   return(LPAREN);     }
")"             {   return(RPAREN);     }
"+"             {   return(ADD);        }
"-"             {   return(SUBT);       }
"*"             {   return(MULT);       }
"/"             {   return(DIV);        }
"="             {   return(EQ);         }
"'"             {   return(QUOTE);      }
[a-zA-Z_][a-zA-Z0-9_]*      {   yylval.s = strdup(yytext);
                                return(STRING);
                            }
%%