//parse.y
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <ctype.h>

    extern int yylex();
    FILE * output;
    bool exist(char* filename);
    void yyerror(char* msg);
    bool identifier(char* id);
%}

%union{
    char* s;
    int i;
}

//* and / have HIGHER PRECEDENCE than - and +
// %left '-' '+'
// %left '*' '/'

%token <i> NUM
%token PROGRAM VAR START END INTEGER PRINT 
%token SEMICOLON COMMA LPAREN RPAREN ADD SUBT MULT DIV EQ QUOTE PERIOD COLON
%token <s> STRING       //Defined in parse.lex as:      [a-zA-Z0-9]+
%type <s> id dec pname
%type <i> assign expr term factor 

%%
start       :   PROGRAM pname semicolon var comma declist semicolon start statlist end period
            |   { yyerror("PROGRAM is expected\n"); }
            ;
pname       :   STRING
            |   { yyerror("Program name is missing\n"); }
            ;
var         :   VAR
            |   { yyerror("VAR is expected\n"); }
            ;
comma       :   COMMA
            |   { yyerror(", is missing\n"); }
            ;
semicolon   :   SEMICOLON
            |   { yyerror(": is missing\n"); }
            ;
end         :   END
            |   { yyerror("END is expected\n"); }
period      :   PERIOD
            |   { yyerror(". is missing\n"); }
id          :   STRING  { if(!identifier($1)) { yyerror("INVALID IDENTIFIER\n"); } }
            ;

declist     :   dec COLON type
            |   dec type        { yyerror(": is missing\n"); }
            ;
dec         :   id COMMA dec    { fprintf(output, "%s, %s", $1, $3); }
            |   id              { fprintf(output, "%s;", $1); }
            ;

statlist    :   stat semicolon
            |   stat semicolon statlist
            ;
stat        :   print
            |   assign
            ;
print       :   PRINT LPAREN output RPAREN  { fprintf(output, "cout << "); }
            |   PRINT output RPAREN { yyerror("( is missing\n"); }
            |   PRINT LPAREN output { yyerror(") is missing\n"); }
            ; 
output      :   STRING COMMA id { fprintf(output, "\"%s\" << %s;", $1, $3); }
            |   id  { fprintf(output, "%s;", $1); }
            |   STRING id { yyerror(", is missing\n"); }
            ;
assign      :   id EQ expr         { $$ = $3; }
            |   id expr { yyerror("= is missing\n"); }
            ;

expr        :   term
            |   expr ADD term       { $$ = $1 + $3; }
            |   expr SUBT term       { $$ = $1 - $3; }
            ;

term        :   term MULT factor     { $$ = $1 * $3; }
            |   term DIV factor     { $$ = $1 / $3; }
            |   factor
            ;

factor      :   id
            |   number
            |   LPAREN expr RPAREN
            |   expr RPAREN     { yyerror("( is missing"); }
            |   LPAREN expr     { yyerror(") is missing"); }
            ;

number      :   digit
            ;
type        :   INTEGER
            ;

digit       :   NUM
            ;

%%

bool exist(char* filename) {
    FILE* checkfile = fopen(filename, "r");      //Pass in "r" since read does not create a file
    if(!checkfile) {
        return false;
    }
    else {
        return true;
    }
}

bool identifier(char* id) {
    char invalid[] = "!@#$%^&*()-+=;:{}|\\\"\',<.>?/ ";      //Invalid characters
    if(isdigit(id[0]) || strpbrk(id, invalid)) {        //First character cannot be a digit, and the whole string cannot have the invalid characters 
        return false;
    }
    else {
        return true;
    }
}

void yyerror(char* msg) {
    printf("Error! %s\n", msg);
} 

int main() {
    //Delete "abc13.cpp" if already exists
    if(exist("abc13.cpp")) {
        remove("abc13.cpp");
    }
    //Create the file "abc13.cpp"
    output = fopen("abc13.cpp", "a");       //Pass "a" to create the file and append to it
    if(!output) {
        fprintf(stderr, "Could not create abc13.cpp!\n");
        exit(1);
    }
    //Init the output file
    fprintf(output, "#include <iostream>\n\nusing namespace std;\n\nint main(int argc, const char* argv[]) {\n");

    yyparse();      //Generate the code by parsing the input

    fprintf(output, "\nreturn 0;\n}");      //The end of the output file
    fclose(output);
}

#include "lex.yy.c"
