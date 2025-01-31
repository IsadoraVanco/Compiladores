%{
#include <iostream>
#include <string.h>
#include "grafo.h"

using std::cout;
using std::endl;

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

%token GRAFO 
%token DOIS_PONTOS IGUAL
%token SETA
%token ID_K
%token <numInt> NUMERO_INTEIRO

%token ERRO

%start inicial
%%

inicial     : nome numeroK associacoes      { return FIM; }
            ;

nome        : GRAFO NUMERO_INTEIRO DOIS_PONTOS      { regalloc->setNumeroId($2); }
            ;

numeroK     : ID_K IGUAL NUMERO_INTEIRO             { regalloc->setNumeroCores($3); }
            ;

associacoes : associa nAssocia
            ;

associa     : NUMERO_INTEIRO SETA valor
            ;

nAssocia    : associa
            | // Vazia
            ;

valor       : NUMERO_INTEIRO nValor                 { }
            ;

nValor      : valor
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