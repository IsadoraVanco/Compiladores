%{
#include <iostream>
#include <string.h>
#include "regalloc.h"

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

%token GRAFO 
%token DOIS_PONTOS IGUAL
%token SETA
%token ID_K
%token <numInt> NUMERO_INTEIRO

%token NOVA_LINHA
%token EoF
%token ERRO

%start inicial
%%

inicial     : nome numeroK associacoes          { return SUCESSO; }
            | EoF                               { /*cout << "Fim do arquivo!\n";*/ return FIM; }                      
            ;

nome        : GRAFO NUMERO_INTEIRO DOIS_PONTOS NOVA_LINHA   { regalloc->setNumeroId($2); }
            ;

numeroK     : ID_K IGUAL NUMERO_INTEIRO NOVA_LINHA          { regalloc->setNumeroCores($3); }
            ;

associacoes : associa nAssocia
            ;

associa     : NUMERO_INTEIRO SETA valor          { regalloc->adicionarVertice($1); }
            ;

nAssocia    : NOVA_LINHA associacoes
            | // Vazia
            ;

valor       : NUMERO_INTEIRO nValor     { regalloc->adicionarAresta($1); }
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