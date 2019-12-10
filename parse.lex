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
"BEGIN"         {   return(BEGIN);      }
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
[a-zA-Z_][a-zA-Z0-9_]+      {   yylval.string = strdup(yytext);
                                return(STRING);
                            }
%%

void yyerror(char* msg) {
    printf("Error! %s\n", msg);
} 
int main() {
    yylex();
}