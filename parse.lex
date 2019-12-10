%{
#include "parse.tab.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool identifier(char* id);
%}

%option noyywrap

number      ([0-9])+

%%
"PROGRAM"       {   return(PROGRAM);    }
"VAR"           {   return(VAR);        }
"BEGIN"         {   return(BEGIN);      }
"END."          {   return(END);        }
"INTEGER"       {   return(INTEGER);    }
"PRINT"         {   return(PRINT);      }
{number}        {   return(NUM);        }
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
[a-zA-Z][a-zA-Z0-9]*    {   return(IDENTIFIER); }

%%

void yyerror(char* msg) {
    printf("Error! %s\n", msg);
} 
int main() {
    yylex();
}