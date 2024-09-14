%{
#include <iostream>
#include <cctype>

using namespace std;

int yylex(void);
int yyparser(void);
void yyerror(const char *);
%}

%token DIGITO

%%

calc    : expr '\n'         { cout << $1 << "\n"; }
        | calc expr '\n'    { cout << $2 << "\n"; }
        ;

expr    : expr '+' term       { $$ = $1 + $3; }
        | term
        ;

term    : term '*' fact     { $$ = $1 * $3; }
        | fact
        ;

fact    : '(' expr ')'      { $$ = $2; }
        | DIGITO 
        ;

%%

int yylex() 
{
    char caractere;
    caractere = cin.get();

    if(isdigit(caractere))
    {
        yylval = caractere - '0';
        return DIGITO;
    }

    return caractere;
}

void yyerror(const char *string)
{
    cout << "[ERRO] " << string << endl;
}

int main()
{
    yyparse();
}