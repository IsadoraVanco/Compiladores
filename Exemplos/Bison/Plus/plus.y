%{
#include <iostream>
#include <cctype>

// Define o tipo dos atributos em yylval
#define YYSTYPE double

using std::cin;
using std::cout;

int yylex(void);
int yyparser(void);
void yyerror(const char *);
%}

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

int yylex() 
{
    char caractere;
    caractere = cin.get();

    while(caractere == ' ')
    {
        caractere = cin.get();
    }

    if(caractere == '.' || isdigit(caractere))
    {
        cin.unget();
        // Lê o valor com o tipo que foi definido em YYSTYPE
        cin >> yylval;

        return NUMERO;
    }

    return caractere;
}

void yyerror(const char *string)
{
    cout << "[ERRO] " << string << "\n";
}

int main()
{
    yyparse();
}