#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "dcmat.h"

using std::cout;

extern int yyparse();
extern int yylex_destroy();

// Variáveis globais
// Funções do dcmat
DCMat *dcmat = nullptr;
// Armazena os limites lidos
Limites *limites;
// Armazena o token que está sendo lido
char *token = NULL;

int main() {
    dcmat = new DCMat();
    limites = new Limites{0, 0};

    int retorno = 1;

    do{
        cout << ">";
        retorno = yyparse();
    }while(retorno);

    delete dcmat;
    delete limites;
    if(token){
        free(token);
    }
    yylex_destroy();

    return 0;
}