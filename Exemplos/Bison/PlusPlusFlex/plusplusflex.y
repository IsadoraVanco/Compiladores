%{
#include <iostream>
#include <unordered_map>
#include <string>

using std::cout;
using std::string;
using std::unordered_map;

int yylex(void);
int yyparser(void);
void yyerror(const char *);

// Tabela de símbolos
unordered_map<string, double> variaveis;
%}

// Define o tipo dos atributos em yylval
%union {
    double numero;
    char variavel[255];
}

%token <numero> NUMERO
%token <variavel> VARIAVEL

%type <numero> expr

%left '+' '-'
%left '*' '/'
%nonassoc NEGATIVO

%%

math    : math calc '\n'
        | calc '\n'
        ;

calc    : VARIAVEL '=' expr         { variaveis[$1] = $3; }
        | expr                      { cout << "= " << $1 << "\n"; }   
        ;

expr    : expr '+' expr             { $$ = $1 + $3; }
        | expr '-' expr             { $$ = $1 - $3; }
        | expr '*' expr             { $$ = $1 * $3; }
        | expr '/' expr             
        { 
            if($3 == 0)
            {
                yyerror("Divisão por zero!");
            }
            else
            {
                $$ = $1 / $3;
            }
        }
        | '(' expr ')'              { $$ = $2; }
        | '-' expr %prec NEGATIVO   { $$ = - $2; }
        | VARIAVEL                  { $$ = variaveis[$1]; }
        | NUMERO                    // $$ = $1
        ;

%%

void yyerror(const char *string)
{
    extern int yylineno;
    extern char *yytext;

    cout << "[ERRO] " << string << "\n";
    cout << "Simbolo: " << yytext << "\n";
    cout << "Linha: " << yylineno << "\n";
    exit(EXIT_FAILURE);
}

int main()
{
    yyparse();
}