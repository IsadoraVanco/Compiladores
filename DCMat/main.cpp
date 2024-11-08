#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "dcmat.h"

using std::cout;

extern int yyparse();
extern int leituraEntrada;

// Variável global do dcmat
DCMat *dcmat = nullptr;

int main() {
    dcmat = new DCMat();

    int retorno = 1;

    do{
        leituraEntrada = true;
        cout << ">";
        retorno = yyparse();
    }while(retorno);

    delete dcmat;

    return 0;
}