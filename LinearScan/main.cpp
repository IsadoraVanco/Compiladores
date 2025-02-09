#include <iostream>
#include "tokens.h"  // Tokens gerados pelo Bison
#include "linearScan.h"

extern int yyparse();
extern int yylex_destroy();
extern void yyfree(void*);

// Variáveis globais

// Funções do grafo
LinearScan *linearScan = nullptr;

// Indica se houve um erro no léxico
bool erroLexico;
// Indica se houve um erro no sintático
bool erroSintatico;

int main() {
    linearScan = new LinearScan();
    erroLexico = false;
    erroSintatico = false;

    int retorno = 1;

    // Verificação da entrada
    do{
        retorno = yyparse();
    }while(retorno);

    // Mostra todos os registradores
    // linearScan->mostrarRegistradores();

    // Faz as alocações
    linearScan->fazerAlocacoes();

    // Resumo das análises
    linearScan->resumirAnalises();

    delete linearScan;
    yylex_destroy();
    yyfree(nullptr);

    return 0;
}