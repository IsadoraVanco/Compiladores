#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "types.h"

using std::cout;

extern int yyparse();
extern int yylex_destroy();

// Variáveis globais

// Armazena o token que está sendo lido
Token *token = NULL;

// Indica se houve um erro no léxico
bool erroLexico;
// Indica se houve um erro no sintático
bool erroSintatico;

int main() {
    erroLexico = false;
    erroSintatico = false;
    token = new Token;

    int retorno = 1;

    do{
        retorno = yyparse();
    }while(retorno);

    delete token;
    yylex_destroy();

    return 0;
}