#include <stdbool.h>

/*****************************************************************
 * DEFINIÇÕES
 *****************************************************************/

typedef struct
{
    short int qtdEstados;        // Guarda o número de estados
    short int estadoInicial;     // Guarda o estado inicial
    short int *estadosFinais;    // Guarda os estados finais
    char **tokens;               // Guarda o token de cada estado
    short int qtdSimbolos;       // Guarda a quantidade máxima de símbolos aceitos
    short int *simbolosValidos;  // Guarda quais são os símbolos válidos
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
 */
void configurarEstadoFinal(Automato *automato, short int numEstado, char *nomeToken);

/**
 * @brief Adiciona uma transição entre dois estados
 * @param automato O endereço do autômato
 * @param estadoOrigem O número estado de origem
 * @param estadoDestino O número do estado de destino
 * @param caractereInicio O caractere do inicio do intervalo de leitura
 * @param caractereFim O caractere que delimita o fim do intervalo de leitura
 */
void adicionarTransicao(Automato *automato, short int estadoOrigem, short int estadoDestino, char caractereInicio, char caractereFim);

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
 * @brief Mostra um token de uma string
 * @param string O endereço da string
 * @param inicio O índice de inicio do token
 * @param fim O indice de fim do token
 */
void mostrarToken(char *string, int inicio, int fim);

/**
 * @brief Analisa a entrada de dados no autômato e classifica os tokens
 * @param automato O endereço do autômato
 * @param entrada A string de entrada do autômato
 * @param tamanho O tamanho da string de entrada
 */
void analisarEntrada(Automato *automato, char *entrada, int tamanho);