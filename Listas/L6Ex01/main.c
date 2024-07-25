#include <stdio.h>
#include <string.h>
#include "automato.h"

int main()
{
    // Configura o autômato
    Automato *automato = criarAutomato(22, 1, 255);

    // Configura o simbolo como desconsiderado
    configurarSimboloDesconsiderado(automato, '\n');
    configurarSimboloDesconsiderado(automato, ' ');

    adicionarTransicao(automato, 1, 2, 'h', 'h');
    adicionarTransicao(automato, 1, 4, 's', 's');
    adicionarTransicao(automato, 1, 11, 'c', 'c');
    adicionarTransicao(automato, 1, 17, '+', '+');
    adicionarTransicao(automato, 1, 18, '-', '-');
    adicionarTransicao(automato, 1, 19, '0', '9');

    adicionarTransicao(automato, 2, 3, 'e', 'e');
    adicionarTransicao(automato, 2, 7, 'i', 'i');

    configurarEstadoFinal(automato, 3, "ELE", true);
    adicionarTransicao(automato, 3, 9, 'r', 'r');

    adicionarTransicao(automato, 4, 5, 'h', 'h');

    adicionarTransicao(automato, 5, 6, 'e', 'e');

    configurarEstadoFinal(automato, 6, "ELA", true);

    adicionarTransicao(automato, 7, 8, 's', 's');

    configurarEstadoFinal(automato, 8, "DELE", true);

    adicionarTransicao(automato, 9, 10, 's', 's');

    configurarEstadoFinal(automato, 10, "DELA", true);

    adicionarTransicao(automato, 11, 12, 'a', 'a');

    adicionarTransicao(automato, 12, 13, 't', 't');
    adicionarTransicao(automato, 12, 14, 'r', 'r');

    configurarEstadoFinal(automato, 13, "GATO", true);
    adicionarTransicao(automato, 13, 15, 's', 's');

    configurarEstadoFinal(automato, 14, "CARRO", true);
    adicionarTransicao(automato, 14, 16, 's', 's');

    configurarEstadoFinal(automato, 15, "GATOS", true);

    configurarEstadoFinal(automato, 16, "CARROS", true);

    configurarEstadoFinal(automato, 17, "MAIS", true);

    configurarEstadoFinal(automato, 18, "MENOS", true);

    configurarEstadoFinal(automato, 19, "INTEIRO", false);
    adicionarTransicao(automato, 19, 19, '0', '9');
    adicionarTransicao(automato, 19, 20, 'e', 'e');

    adicionarTransicao(automato, 20, 21, '+', '+');
    adicionarTransicao(automato, 20, 21, '-', '-');
    adicionarTransicao(automato, 20, 22, '0', '9');

    adicionarTransicao(automato, 21, 22, '0', '9');

    configurarEstadoFinal(automato, 22, "REAL", false);
    adicionarTransicao(automato, 22, 22, '0', '9');

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