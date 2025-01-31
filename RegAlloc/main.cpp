#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "grafo.h"

using std::cout;

extern int yyparse();
extern int yylex_destroy();

// Variáveis globais

// Funções do grafo
Grafo *regalloc = nullptr;

// Indica se houve um erro no léxico
bool erroLexico;
// Indica se houve um erro no sintático
bool erroSintatico;

int main() {
    regalloc = new Grafo();
    erroLexico = false;
    erroSintatico = false;

    int retorno = 1;

    // Verificação da entrada
    do{
        retorno = yyparse();
    }while(retorno);

    // Mostra as configurações
    regalloc->mostrarConfiguracoes();

    // Avaliação da coloração

    // Resumo das análises


    delete regalloc;
    yylex_destroy();

    return 0;
}