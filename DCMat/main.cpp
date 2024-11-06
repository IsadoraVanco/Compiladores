#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison

using std::cout;

extern int yyparse();
extern int leituraEntrada;

int main() {
    int retorno = 1;

    do{
        leituraEntrada = true;
        cout << ">";
        retorno = yyparse();
    }while(retorno);

    return 0;
}