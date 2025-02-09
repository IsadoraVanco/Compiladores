%{
#include <iostream>
#include <string.h>
#include "linearScan.h"

using std::cout;

extern int yytext;

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
// Tipos de retornos
enum { FIM = 0, SUCESSO};

int yylex(void);
int yyparser(void);
void yyerror(const void *string);
%}

%union {
    unsigned int numInt;
}

%defines "tokens.h"

%token REG_VIRTUAL 
%token IGUAL
%token SETA
%token ID_K
%token <numInt> NUMERO_INTEIRO

%token EoF
%token ERRO

%start inicial
%%

inicial     : numeroK tempos    { return SUCESSO; }
            | EoF               { /*cout << "Fim do arquivo!\n";*/ return FIM; }                      
            ;

numeroK     : ID_K IGUAL NUMERO_INTEIRO     { linearScan->setNumeroRegistradores($3); }
            ;

tempos : associa nAssocia
            ;

associa     : REG_VIRTUAL NUMERO_INTEIRO SETA NUMERO_INTEIRO NUMERO_INTEIRO     { linearScan->adicionarRegistradorVirtual($2, $4, $5); }
            ;

nAssocia    : tempos
            | // Vazia
            ;

%%

int emitirErroSintatico(int erro)
{
    cout << "\nSYNTAX ERROR: ";

    switch(erro)
    {
        case TOKEN_FALTANTE:
            cout << "Incomplete Command\n\n";
            break;

        case TOKEN_INESPERADO:
            cout << "Token inesperado\n\n";
            break;

        default:
            break;
    }

    return SUCESSO;
}

void yyerror(const void *string)
{

}