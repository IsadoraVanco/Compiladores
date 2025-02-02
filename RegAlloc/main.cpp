#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "regalloc.h"

using std::cout;

extern int yyparse();
extern int yylex_destroy();

// Variáveis globais

// Funções do grafo
RegAlloc *regalloc = nullptr;

// Indica se houve um erro no léxico
bool erroLexico;
// Indica se houve um erro no sintático
bool erroSintatico;

int main() {
    regalloc = new RegAlloc();
    erroLexico = false;
    erroSintatico = false;

    int retorno = 1;

    // Verificação da entrada
    do{
        // cout << "=> NOVO\n";
        retorno = yyparse();
    }while(retorno);

    // Mostra as configurações
    regalloc->mostrarConfiguracoes();
    // regalloc->mostrarGrafo();

    // Avaliação da coloração
    regalloc->avaliarColoracoes();

    // Resumo das análises
    regalloc->resumirAnalises();

    delete regalloc;
    yylex_destroy();

    return 0;
}