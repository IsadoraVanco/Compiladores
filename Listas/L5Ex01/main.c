#include <stdio.h>
#include <string.h>
#include "automato.h"

int main()
{
    // Configura o autômato
    Automato *automato = criarAutomato(8, 1, 'z');

    adicionarTransicao(automato, 1, 5, '0', '9');
    adicionarTransicao(automato, 1, 2, 'a', 'z');
    adicionarTransicao(automato, 1, 3, '+', '+');
    adicionarTransicao(automato, 1, 4, '-', '-');

    configurarEstadoFinal(automato, 2, "");
    adicionarTransicao(automato, 2, 2, '0', '9');
    adicionarTransicao(automato, 2, 2, 'a', 'z');

    configurarEstadoFinal(automato, 3, "");
    configurarEstadoFinal(automato, 4, "");

    configurarEstadoFinal(automato, 5, "");
    adicionarTransicao(automato, 5, 5, '0', '9');
    adicionarTransicao(automato, 5, 6, 'e', 'e');

    adicionarTransicao(automato, 6, 8, '0', '9');
    adicionarTransicao(automato, 6, 7, '+', '+');
    adicionarTransicao(automato, 6, 7, '-', '-');

    adicionarTransicao(automato, 7, 8, '0', '9');

    configurarEstadoFinal(automato, 8, "");
    adicionarTransicao(automato, 8, 8, '0', '9');

    char entrada[200];

    while (1)
    {
        // printf("=>");

        // ctrl + z (windows) e ctrl + d (linux)
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            break;
        }

        // Remove o \n
        entrada[strcspn(entrada, "\n")] = '\0';
        analisarEntrada(automato, entrada, strlen(entrada));
    }

    deletarAutomato(automato);
    // printf("\n-> Obrigada! :)\n");

    return 0;
}