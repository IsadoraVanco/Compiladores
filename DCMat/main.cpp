#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "dcmat.h"
#include "ast.h"

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
// Armazena o endereço do node atual
NodeArvore *nodeLeitura;

// Indica se houve um erro no léxico
bool erroLexico;
// Indica se houve um erro no sintático
bool erroSintatico;

int main() {
    dcmat = new DCMat();
    limites = new Limites{0, 0};
    erroLexico = false;
    erroSintatico = false;

    int retorno = 1;

    do{
        if(!erroSintatico && !erroLexico){
            cout << ">";
        }

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