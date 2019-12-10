//parse.y
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    extern int yylex();
    FILE * output;
    void yyerror(char* msg);

%}

%union{
    char* s;
    int i;
}

//* and / have HIGHER PRECEDENCE than - and +
%left '-' '+'
%left '*' '/'

%token <i> NUM
%token PROGRAM VAR BEGIN END INTEGER PRINT 
%token SEMICOLON COMMA LPAREN RPAREN ADD SUBT MULT DIV EQ QUOTE
%token <s> STRING       //Defined in parse.lex as:      [a-zA-Z0-9]+
%type <s> id 
%type <i> expr term factor 

%%
start       :   PROGRAM pname SEMICOLON VAR COMMA declist SEMICOLON BEGIN statlist END PERIOD
            ;
pname       :   STRING
            ;
id          :   letter L
            |   letter
            ;
L           :   letter L
            |   letter
            |   digit L
            |   digit
            ;

declist     :   dec COLON type
            ;
dec         :   id COMMA dec    { fprintf(output, "%s, %s", $1, $3); }
            |   id              { fprintf(output, "%s;", $1); }
            ;

statlist    :   stat SEMICOLON
            |   stat SEMICOLON statlist
            ;
stat        :   print
            |   assign
            ;
print       :   PRINT LPAREN output RPAREN  { fprintf(output, "cout << "); }
            ;
output      :   STRING COMMA id { fprintf(output, "\"%s\", %s;", %1, %3); }
            |   id  { fprintf(output, "%s", $1); }
            ;
assign      :   id EQ expr         { $$ = $3; }
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
            ;

number      :   digit
            ;
type        :   INTEGER
            ;

digit       :   NUM
            ;

letter      :   'a' | 'b' | 'c' | 'd' | 'e' | 'f'
            ;
%%

bool exist(char* filename) {
    FILE* checkfile = fopen(filename, "r");      //Pass in "r" since read does not create a file
    if(!fopen) {
        return false;
    }
    else {
        return true;
    }
}

int main() {
    //Delete "abc13.cpp" if already exists
    if(exist("abc13.cpp")) {
        remove("abc13.cpp");
    }
    //Create the file "abc13.cpp"
    output = fopen("abc13.cpp", "a");       //Pass "a" to create the file and append to it
    if(!fopen) {
        fprintf(stderr, "Could not create abc13.cpp!\n";);
        exit(1);
    }
    //Init the output file
    fprintf(output, "#include <iostream>\n\nusing namespace std;\n\nint main(int argc, const char* argv[]) {\n");

    yyparse();      //Generate the code by parsing the input

    fprintf(output, "\nreturn 0;\n}");      //The end of the output file
    fclose(output);
}

void yyerror(char* msg) {
    printf("Error! %s\n", msg);
} 
#include "lex.yy.c"
