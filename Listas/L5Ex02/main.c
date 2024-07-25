#include <stdio.h>
#include <string.h>
#include "automato.h"

int main()
{
    // Configura o autômato
    Automato *automato = criarAutomato(13, 1, 255);

    // Sobreescreve o estado inválido
    adicionarTransicao(automato, 1, 13, 0, 255);

    // Configura o simbolo como desconsiderado para todas as transições
    configurarSimboloDesconsiderado(automato, '\n');

    adicionarTransicao(automato, 1, 4, 'a', 'z');
    adicionarTransicao(automato, 1, 2, 'i', 'i');
    adicionarTransicao(automato, 1, 5, '.', '.');
    adicionarTransicao(automato, 1, 7, '0', '9');
    adicionarTransicao(automato, 1, 9, '-', '-');
    adicionarTransicao(automato, 1, 12, ' ', ' ');

    configurarEstadoFinal(automato, 2, "ID", false);
    adicionarTransicao(automato, 2, 4, 'a', 'z');
    adicionarTransicao(automato, 2, 4, '0', '9');
    adicionarTransicao(automato, 2, 3, 'f', 'f');

    configurarEstadoFinal(automato, 3, "IF", false);
    adicionarTransicao(automato, 3, 4, 'a', 'z');
    adicionarTransicao(automato, 3, 4, '0', '9');

    configurarEstadoFinal(automato, 4, "ID", false);
    adicionarTransicao(automato, 4, 4, 'a', 'z');
    adicionarTransicao(automato, 4, 4, '0', '9');

    configurarEstadoFinal(automato, 5, "error", false);
    adicionarTransicao(automato, 5, 6, '0', '9');

    configurarEstadoFinal(automato, 6, "REAL", false);
    adicionarTransicao(automato, 6, 6, '0', '9');

    configurarEstadoFinal(automato, 7, "NUM", false);
    adicionarTransicao(automato, 7, 7, '0', '9');
    adicionarTransicao(automato, 7, 8, '.', '.');

    configurarEstadoFinal(automato, 8, "REAL", false);
    adicionarTransicao(automato, 8, 8, '0', '9');

    configurarEstadoFinal(automato, 9, "error", false);
    adicionarTransicao(automato, 9, 10, '-', '-');

    adicionarTransicao(automato, 10, 10, 'a', 'z');
    adicionarTransicao(automato, 10, 11, '\n', '\n');

    configurarEstadoFinal(automato, 11, "comment", false);

    configurarEstadoFinal(automato, 12, "white space", true);
    adicionarTransicao(automato, 12, 12, ' ', ' ');

    configurarEstadoFinal(automato, 13, "error", false);

    char entrada[200];

    while (1)
    {
        // printf("=>");

        // ctrl + z (windows) e ctrl + d (linux)
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            break;
        }

        identificarTokens(automato, entrada, strlen(entrada));
    }

    deletarAutomato(automato);
    // printf("\n-> Obrigada! :)\n");

    return 0;
}