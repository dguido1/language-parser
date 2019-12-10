%{
#include "parse.tab.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"

bool identifier(char* id);
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
";"             {   return(SEMICOLON);  }
","             {   return(COMMA);      }
"("             {   return(PAREN);      }
")"             {   return(PAREN);      }
"+"             {   return(OP);         }
"-"             {   return(OP);         }
"*"             {   return(OP);         }
"/"             {   return(OP);         }

%%

bool identifier(char* id) {
    char invalid[] = "!@#$%^&*()-+=;:{}|\\\"\',<.>?/ ";      //Invalid characters
    if(isdigit(id[0]) || strpbrk(id, invalid)) {        //First character cannot be a digit, and the whole string cannot have the invalid characters 
        return false;
    }
    else {
        return true;
    }
}
int main() {
    yylex();
    return 0;
}