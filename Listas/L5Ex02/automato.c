#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

/*****************************************************************
 * DEFINIÇÕES
 *****************************************************************/

#define ESTADO_DESCONSIDERADO -1
#define ESTADO_INVALIDO 0
#define ESTADO_FINAL 1

/*****************************************************************
 * FUNÇÕES DE CONFIGURAÇÃO
 *****************************************************************/

Automato *criarAutomato(short int numEstados, short int estadoInicial, short int numSimbolos)
{
    if (numEstados <= 0)
    {
        printf("[Automato][ERRO] Número de estados insuficiente: %d\n", numEstados);
        return NULL;
    }

    if (numSimbolos <= 0)
    {
        printf("[Automato][ERRO] Número de símbolos insuficiente: %d\n", numSimbolos);
        return NULL;
    }

    if (estadoInicial < 0 || estadoInicial > numEstados || estadoInicial == ESTADO_INVALIDO)
    {
        printf("[Automato][ERRO] Não é possível definir o estado inicial como %d\n", estadoInicial);
        return NULL;
    }

    Automato *novo = (Automato *)malloc(sizeof(Automato));

    novo->qtdEstados = numEstados;
    novo->estadoInicial = estadoInicial;

    // Contando com o estado inválido
    short int totalEstados = numEstados + 1;

    novo->estadosFinais = (short int *)calloc(totalEstados, sizeof(short int));
    if (novo->estadosFinais == NULL)
    {
        free(novo);
        printf("[Automato][ERRO] Falha ao alocar espaço para os estados finais\n");

        return NULL;
    }

    novo->tokens = (char **)calloc(totalEstados, sizeof(char *));
    if (novo->tokens == NULL)
    {
        free(novo->estadosFinais);
        free(novo);
        printf("[Automato][ERRO] Falha ao alocar espaço para os tokens\n");

        return NULL;
    }

    // Contando com o (0)
    novo->qtdSimbolos = numSimbolos + 1;

    novo->matrizTransicao = (short int **)malloc(totalEstados * sizeof(short int *));
    if (novo->matrizTransicao == NULL)
    {
        free(novo->tokens);
        free(novo->estadosFinais);
        free(novo);
        printf("[Automato][ERRO] Falha ao alocar espaço para a matriz de transição\n");

        return NULL;
    }

    for (int i = 0; i < totalEstados; i++)
    {
        novo->matrizTransicao[i] = (short int *)malloc((numSimbolos + 1) * sizeof(short int));
        for (int j = 0; j < numSimbolos; j++)
        {
            novo->matrizTransicao[i][j] = ESTADO_INVALIDO;
        }
    }

    return novo;
}

void configurarEstadoFinal(Automato *automato, short int numEstado, char *nomeToken, bool mostrarApenasToken)
{
    if (!ehEstadoValido(automato, numEstado))
    {
        printf("[Automato][ERRO] Não é possível configurar o estado %d: estado inválido\n", numEstado);
        return;
    }

    if (mostrarApenasToken)
    {
        automato->estadosFinais[numEstado] = ESTADO_FINAL;
    }
    else
    {
        automato->estadosFinais[numEstado] = ESTADO_FINAL * (-1);
    }

    automato->tokens[numEstado] = strdup(nomeToken);
}

void configurarSimboloDesconsiderado(Automato *automato, short int simbolo)
{
    if (simbolo > automato->qtdSimbolos)
    {
        printf("[Automato][ERRO] Não é possível configurar o símbolo '%d' como desconsiderado\n", simbolo);
        return;
    }

    for (int estado = automato->qtdEstados; estado > 0; estado--)
    {
        automato->matrizTransicao[estado][simbolo] = ESTADO_DESCONSIDERADO;
    }
}

void adicionarTransicao(Automato *automato, short int estadoOrigem, short int estadoDestino,
                        short int caractereInicio, short int caractereFim)
{
    if (!ehEstadoValido(automato, estadoOrigem))
    {
        printf("[Automato][ERRO] Não é possível adicionar transição do estado de origem %d: estado inválido\n", estadoOrigem);
        return;
    }

    if (!ehEstadoValido(automato, estadoDestino))
    {
        printf("[Automato][ERRO] Não é possível adicionar transição para estado destino %d: estado inválido\n", estadoOrigem);
        return;
    }

    if (caractereFim < caractereInicio || caractereFim > automato->qtdSimbolos ||
        caractereInicio > automato->qtdSimbolos)
    {
        printf("[Automato][ERRO] Não é possível adicionar transição para os caracteres %c ou %c\n", (char) caractereInicio, (char) caractereFim);
        return;
    }

    for (short int i = caractereInicio; i <= caractereFim; i++)
    {
        automato->matrizTransicao[estadoOrigem][i] = (short int)estadoDestino;
    }
}

/*****************************************************************
 * FUNÇÕES BÁSICAS
 *****************************************************************/

bool ehEstadoValido(Automato *automato, short int numEstado)
{
    return numEstado >= 0 && numEstado <= automato->qtdEstados && numEstado != ESTADO_INVALIDO;
}

bool ehEstadoFinal(Automato *automato, short int numEstado)
{
    return automato->estadosFinais[numEstado] == ESTADO_FINAL ||
           automato->estadosFinais[numEstado] == (-1) * ESTADO_FINAL;
}

void deletarAutomato(Automato *automato)
{
    free(automato->estadosFinais);

    for (int i = 0; i <= automato->qtdEstados; i++)
    {
        free(automato->tokens[i]);
        free(automato->matrizTransicao[i]);
    }
    free(automato->tokens);
    free(automato->matrizTransicao);

    free(automato);
}

/*****************************************************************
 * FUNÇÕES DE MANIPULAÇÃO
 *****************************************************************/

void mostrarToken(Automato *automato, int numEstado, char *string,
                  int inicioSubString, int fimSubString)
{
    if (automato->estadosFinais[numEstado] < 0)
    {
        int tamanho = fimSubString - inicioSubString + 1;
        char subString[tamanho + 1];

        strncpy(subString, &string[inicioSubString], tamanho);

        // Ignora o '\n' do fim
        if(subString[tamanho - 1] == '\n'){
            subString[tamanho - 1] = '\0';
        }else{
            subString[tamanho] = '\0';
        }

        printf("%s ", subString);
    }

    printf("%s\n", automato->tokens[numEstado]);
}

void identificarTokens(Automato *automato, char *entrada, int tamanho)
{
    int indiceAtual = 0;
    int indiceInicioToken = 0;
    int indiceFimToken = -1;

    int estadoAtual = automato->estadoInicial;
    int proximoEstado = ESTADO_INVALIDO;
    int ultimoEstadoFinal = ESTADO_INVALIDO;

    // printf("tamanho %d\n", tamanho);
    while (indiceInicioToken < tamanho)
    {
        // Verifica se é o último caractere
        if (indiceAtual >= tamanho)
        {
            // Se há um token reconhecido
            if (indiceFimToken >= indiceInicioToken)
            {
                mostrarToken(automato, ultimoEstadoFinal, entrada,
                             indiceInicioToken, indiceFimToken);
                estadoAtual = automato->estadoInicial;

                indiceInicioToken = indiceFimToken + 1;

                // Se ainda há caracteres que podem ser reconhecidos
                if (indiceInicioToken < indiceAtual)
                {
                    // Reseta o indice
                    indiceAtual = indiceInicioToken;
                }
            }
            else
            {
                indiceInicioToken++;
                indiceAtual = indiceInicioToken;
            }
        }
        else
        {
            short int caractereAtual = entrada[indiceAtual];
            // printf("caractere [%d] indAtual [%d]\n", caractereAtual, indiceAtual);

            // Analisa os caracteres e atualiza o estado
            proximoEstado = automato->matrizTransicao[estadoAtual][caractereAtual];
            // printf("estado atual [%d] prox estado [%d]\n", estadoAtual, proximoEstado);
            // printf("inicio [%d] fim [%d]\n", indiceInicioToken, indiceFimToken);

            // Verifica o próximo estado
            if (proximoEstado == ESTADO_DESCONSIDERADO)
            {
                indiceFimToken = indiceAtual;
                indiceAtual++;
            }
            else if (proximoEstado == ESTADO_INVALIDO)
            {
                // Verifica se o último token foi definido
                if (indiceFimToken >= indiceInicioToken)
                {
                    mostrarToken(automato, ultimoEstadoFinal, entrada,
                                 indiceInicioToken, indiceFimToken);
                    indiceInicioToken = indiceFimToken + 1;
                    indiceFimToken = -1;

                    // Passa o indice atual para o inicio do proximo token
                    indiceAtual = indiceInicioToken;
                }
                else
                {
                    // Volta o indice atual para o proximo indice do começo para avaliar
                    indiceAtual = indiceInicioToken + 1;
                    indiceInicioToken++;
                }

                // Volta para o estado inicial
                estadoAtual = automato->estadoInicial;
            }
            else
            {
                // Marca se é final
                if (ehEstadoFinal(automato, proximoEstado))
                {
                    ultimoEstadoFinal = proximoEstado;
                    indiceFimToken = indiceAtual;
                }

                indiceAtual++;
                estadoAtual = proximoEstado;
            }
        }
    }
}