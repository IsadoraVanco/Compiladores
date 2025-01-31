%option noyywrap
%{
#include <iostream>
#include <string>
#include "tokens.h"

using std::cout;
using std::string;

// Tipos de erros
enum {TOKEN_DESCONHECIDO};

// Protótipos de funções
int emitirErroLexico(int erro);
%}

/* Declarações regulares */
/* Gerais */
decimal     [0-9]
espaco      [ \t]
nova_linha  \n

/* Definições */
num_int     {decimal}+
seta        "-->"
id_k        [Kk]

%%

Grafo           return GRAFO;

":"             return DOIS_PONTOS;
"="             return IGUAL;

{seta}          return SETA;
{id_k}          return ID_K;

{num_int}       {
                    yylval.numInt = atoi(yytext);
                    return NUMERO_INTEIRO;
}

{espaco}        ;
{nova_linha}    ;

.               return emitirErroLexico(TOKEN_DESCONHECIDO); 

%%

int emitirErroLexico(int erro)
{
    switch(erro)
    {
        case TOKEN_DESCONHECIDO:
            cout << "\nInvalid Symbol: " << yytext << "\n\n";
        break;

        default:
            break;
    }

    return ERRO;
}