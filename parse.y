//parse.y
%{
    extern int yylex();
    void yyerror(char* msg);

%}

%union{
    string s;
    int i;
}

//* and / have HIGHER PRECEDENCE than - and +
%left '-' '+'
%left '*' '/'

%token <s> PROGRAM
%token <s> VAR
%token <s> BEGIN
%token <s> END
%token <i> INTEGER
%token <s> PRINT
%token <s> STRING

%%

start       :   PROGRAM pname ';' VAR ',' declist ';' BEGIN statlist END '.'
pname       :   id

id          :   letter L
            |   letter
L           :   letter L
            |   letter
            |   digit L
            |   digit

declist     :   dec ':' type
dec         :   id ',' dec
            |   id

statlist    :   stat ';'
            |   stat ';' statlist
stat        :   print
            |   assign
print       :   PRINT '(' output ')'
output      :   STRING ',' id
            |   id
assign      :   id '=' expr         { $1 = $3; }

expr        :   term
            |   expr '+' term       { $$ = $1 + $3; }
            |   expr '-' term       { $$ = $1 - $3; }
term        :   term '*' factor     { $$ = $1 * $3; }
            |   term '/' factor     { $$ = $1 / $3; }
            |   factor
factor      :   id
            |   number
            |   '(' expr ')'
number      :   digit
            |   digit number
type        :   INTEGER
digit       :   '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
letter      :   'a' | 'b' | 'c' | 'd' | 'e' | 'f'
%%