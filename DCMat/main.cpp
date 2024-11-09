#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "dcmat.h"

using std::cout;

extern int yyparse();
extern int leituraEntrada;

// Variáveis globais
// Funções do dcmat
DCMat *dcmat = nullptr;
Limites *limites;

int main() {
    dcmat = new DCMat();
    limites = new Limites{0, 0};

    int retorno = 1;

    do{
        leituraEntrada = true;
        cout << ">";
        retorno = yyparse();
    }while(retorno);

    delete dcmat;
    delete limites;

    return 0;
}