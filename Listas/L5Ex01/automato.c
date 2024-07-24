#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

/*****************************************************************
 * DEFINIÇÕES
 *****************************************************************/

#define ESTADO_INVALIDO 0
#define ESTADO_FINAL 1

#define CARACTERE_INVALIDO -1
#define CARACTERE_VALIDO 1

/*****************************************************************
 * FUNÇÕES DE CONFIGURAÇÃO
 *****************************************************************/

Automato *criarAutomato(short int numEstados, short int estadoInicial, short int numSimbolos)
{
    if(numEstados <= 0){
        printf("[Automato][ERRO] Número de estados insuficiente: %d\n", numEstados);
        return NULL;
    }

    if(numSimbolos <= 0){
        printf("[Automato][ERRO] Número de símbolos insuficiente: %d\n", numSimbolos);
        return NULL;
    }

    if(estadoInicial < 0 || estadoInicial > numEstados || estadoInicial == ESTADO_INVALIDO){
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
    novo->simbolosValidos = (short int *)malloc((numSimbolos + 1) * sizeof(short int));
    if (novo->simbolosValidos == NULL)
    {
        free(novo->tokens);
        free(novo->estadosFinais);
        free(novo);
        printf("[Automato][ERRO] Falha ao alocar espaço para os caracteres válidos\n");

        return NULL;
    }

    for (int i = 0; i <= numSimbolos; i++)
    {
        novo->simbolosValidos[i] = (short int)CARACTERE_INVALIDO;
    }

    novo->matrizTransicao = (short int **)malloc(totalEstados * sizeof(short int *));
    if (novo->matrizTransicao == NULL)
    {
        free(novo->simbolosValidos);
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

void configurarEstadoFinal(Automato *automato, short int numEstado, char *nomeToken)
{
    if (!ehEstadoValido(automato, numEstado))
    {
        printf("[Automato][ERRO] Não é possível configurar o estado %d: estado inválido\n", numEstado);
        return;
    }

    automato->estadosFinais[numEstado] = ESTADO_FINAL;
    automato->tokens[numEstado] = strdup(nomeToken);
}

void adicionarTransicao(Automato *automato, short int estadoOrigem, short int estadoDestino,
                        char caractereInicio, char caractereFim)
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

    if (caractereFim > automato->qtdSimbolos || caractereInicio > automato->qtdSimbolos)
    {
        printf("[Automato][ERRO] Não é possível adicionar transição para os caracteres %c ou %c\n", caractereInicio, caractereFim);
        return;
    }

    for (short int i = caractereInicio; i <= caractereFim; i++)
    {
        automato->matrizTransicao[estadoOrigem][i] = (short int)estadoDestino;
        automato->simbolosValidos[i] = (short int)CARACTERE_VALIDO;
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
    return automato->estadosFinais[numEstado] != ESTADO_INVALIDO;
}

void deletarAutomato(Automato *automato)
{
    free(automato->estadosFinais);
    free(automato->simbolosValidos);

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

void mostrarToken(char *string, int inicio, int fim)
{
    int tamanho = fim - inicio + 1;
    char token[tamanho + 1];

    strncpy(token, &string[inicio], tamanho);
    token[tamanho] = '\0';

    printf("%s\n", token);
}

void analisarEntrada(Automato *automato, char *entrada, int tamanho)
{
    int indiceAtual = 0;
    int indiceInicioToken = 0;
    int indiceFimToken = -1;

    int estadoAtual = automato->estadoInicial;
    int proximoEstado = ESTADO_INVALIDO;
    // int ultimoEstadoFinal = ESTADO_INVALIDO;

    bool caractereInvalido = false;

    while (indiceInicioToken < tamanho)
    {
        char caractereAtual = entrada[indiceAtual];
        // printf("caractere %c\n", caractereAtual);

        // Analisa os caracteres e atualiza o estado
        proximoEstado = automato->matrizTransicao[estadoAtual][caractereAtual];

        if (automato->simbolosValidos[caractereAtual] == CARACTERE_INVALIDO &&
            indiceAtual == indiceInicioToken)
        {
            caractereInvalido = true;
        }

        // printf("estado %d\n", proximoEstado);

        // Verifica se é inválido
        if (proximoEstado == ESTADO_INVALIDO)
        {
            // printf("inicio %d fim %d\n", indiceInicioToken, indiceFimToken);
            // printf("estado %d indAtual %d\n", proximoEstado, indiceAtual);

            // Verifica se o último token foi definido
            if (indiceFimToken >= indiceInicioToken)
            {
                mostrarToken(entrada, indiceInicioToken, indiceFimToken);
                indiceInicioToken = indiceFimToken + 1;
                indiceFimToken = -1;

                // Passa o indice atual para o inicio do proximo token
                indiceAtual = indiceInicioToken;
            }
            else
            {
                // Volta o indice atual para o proximo indice do começo para avaliar
                indiceAtual = indiceInicioToken + 1;
                indiceInicioToken = indiceInicioToken + 1;
            }

            // Verifica se é caractere inválido
            if (caractereInvalido && indiceAtual == indiceInicioToken)
            {
                printf("ERRO\n");
                caractereInvalido = false;
            }

            // Volta para o estado inicial
            estadoAtual = automato->estadoInicial;
        }
        else
        {
            // Marca se é final
            if (ehEstadoFinal(automato, proximoEstado))
            {
                // ultimoEstadoFinal = proximoEstado;
                indiceFimToken = indiceAtual;
            }

            // Ultimo caractere
            if (indiceAtual >= tamanho - 1)
            {
                if (indiceFimToken >= indiceInicioToken)
                {
                    mostrarToken(entrada, indiceInicioToken, indiceFimToken);
                    estadoAtual = automato->estadoInicial;
                }

                indiceInicioToken = indiceFimToken + 1;

                if (indiceInicioToken < indiceAtual)
                {
                    indiceAtual = indiceInicioToken;
                }
            }
            else
            {
                indiceAtual++;
                estadoAtual = proximoEstado;
            }
        }
    }
}
