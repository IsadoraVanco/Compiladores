%{
#include <iostream>
#include <cctype>

using std::cout;

int yylex(void);
int yyparser(void);
void yyerror(const char *);
%}

// Define o tipo dos atributos em yylval
// Quando é integrado com o Flex
%define api.value.type {double}

%token NUMERO

%left '+' '-'
%left '*' '/'
%nonassoc NEGATIVO

%%

calc    : calc expr '\n'            { cout << $2 << "\n"; }
        | calc '\n'
        | // Vazia
        ;

expr    : expr '+' expr             { $$ = $1 + $3; }
        | expr '-' expr             { $$ = $1 - $3; }
        | expr '*' expr             { $$ = $1 * $3; }
        | expr '/' expr             { $$ = $1 / $3; }
        | '(' expr ')'              { $$ = $2; }
        | '-' expr %prec NEGATIVO   { $$ = - $2; }
        | NUMERO 
        ;

%%

void yyerror(const char *string)
{
    cout << "[ERRO] " << string << "\n";
}

int main()
{
    yyparse();
}