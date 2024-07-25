#ifndef _AUTOMATO_H_
#define _AUTOMATO_H_

#include <stdbool.h>

/*****************************************************************
 * DEFINIÇÕES
 *****************************************************************/

typedef struct
{
    short int qtdEstados;        // Guarda o número de estados (não considera o inválido)
    short int estadoInicial;     // Guarda o estado inicial
    short int *estadosFinais;    // Guarda os estados finais
    char **tokens;               // Guarda o token de cada estado
    short int qtdSimbolos;       // Guarda a quantidade máxima de símbolos aceitos (considera desde o símbolo 0)
    short int **matrizTransicao; // Guarda a matriz de transição de estados
} Automato;

/*****************************************************************
 * FUNÇÕES DE CONFIGURAÇÃO
 *****************************************************************/

/**
 * @brief Cria uma estrutura de autômato
 * @param numEstados O número de estados totais do autômato
 * @param estadoInicial O estado inicial do autômato
 * @param numSimbolos Número de símbolos aceitos pelo autômato
 * @return O endereço do novo autômato
 */
Automato *criarAutomato(short int numEstados, short int estadoInicial, short int numSimbolos);

/**
 * @brief Configura um estado como final
 * @param automato O endereço do autômato
 * @param numEstado O número do estado
 * @param nomeToken O nome do token que o estado terá
 * @param mostrarApenasToken Configura se mostrará apenas o nome do token na identificação
 */
void configurarEstadoFinal(Automato *automato, short int numEstado, char *nomeToken, bool mostrarApenasToken);

/**
 * @brief Configura um símbolo para ser desconsiderado em todas as transições
 * @param automato O endereço do autômato
 * @param simbolo O símbolo a ser desconsiderado
 */
void configurarSimboloDesconsiderado(Automato *automato, short int simbolo);

/**
 * @brief Configura um símbolo para ser neutro em todas as transições
 * @param automato O endereço do autômato
 * @param simbolo O símbolo neutro
 */
void configurarSimboloNeutro(Automato *automato, short int simbolo);

/**
 * @brief Adiciona uma transição entre dois estados
 * @param automato O endereço do autômato
 * @param estadoOrigem O número estado de origem
 * @param estadoDestino O número do estado de destino
 * @param caractereInicio O caractere do inicio do intervalo de leitura
 * @param caractereFim O caractere que delimita o fim do intervalo de leitura
 */
void adicionarTransicao(Automato *automato, short int estadoOrigem, short int estadoDestino, short int caractereInicio, short int caractereFim);

/*****************************************************************
 * FUNÇÕES BÁSICAS
 *****************************************************************/

/**
 * @brief Verifica se um estado de um autômato é válido
 * @param automato O endereço do autômato
 * @param numEstado O número do estado
 * @return Valor lógico da verificação
 */
bool ehEstadoValido(Automato *automato, short int numEstado);

/**
 * @brief Verifica se um estado de um autômato é final
 * @param automato O endereço do autômato
 * @param numEstado O número do estado
 * @return Valor lógico da verificação
 */
bool ehEstadoFinal(Automato *automato, short int numEstado);

/**
 * @brief Deleta um autômato da memória
 * @param automato O endereço do autômato
 */
void deletarAutomato(Automato *automato);

/*****************************************************************
 * FUNÇÕES DE MANIPULAÇÃO
 *****************************************************************/

/**
 * @brief Mostra Uma substring e seu token correspondente
 * @param automato O endereço do autômato
 * @param numEstado O número do estado final
 * @param string A string que será mostrada
 * @param inicioSubString O inicio da substring
 * @param fimSubString O fim da substring
 */
void mostrarToken(Automato *automato, int numEstado, char *string,
                  int inicioSubString, int fimSubString);

/**
 * @brief Analisa a entrada de dados no autômato e classifica os tokens
 * @param automato O endereço do autômato
 * @param entrada A string de entrada do autômato
 * @param tamanho O tamanho da string de entrada
 */
void identificarTokens(Automato *automato, char *entrada, int tamanho);

#endif