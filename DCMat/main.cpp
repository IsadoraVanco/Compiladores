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
    yylex_destroy();

    return 0;
}