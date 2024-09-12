#ifndef _LEXER_H_
#define _LEXER_H_

#include "token.h"

#include <string>
#include <vector>

class Lexer
{
private:
    // Marca a linha e coluna de onde está analisando
    int numeroLinha = 1;
    int numeroColuna = 1;

    // Guarda as linhas lidas
    std::vector<std::string> entradas;

    // Número de estados válidos
    int numeroEstados = 0;
    // Estado inicial do autômato
    int estadoInicial;
    
    /*
    Armazena quais são estados finais 
    (conta com o estado inválido)
    */
    int *estadosFinais;
    /* 
    Guarda o token que será reconhecido 
    em cada estado final (conta com o estado inválido)
    */
    Token *tokens;
    /*
    A matriz de transição do autômato
    (conta com o estado inválido)
    */
    int **matrizTransicao = nullptr;

    /*****************************************************************
     * MÉTODOS PARA LOGS E SAÍDA DE DADOS
     *****************************************************************/

    /**
     * @brief Emite um erro padronizado para a classe
     */
    void emitirErro(std::string erro);

public:
    /*****************************************************************
     * MÉTODOS DE CONFIGURAÇÃO
     *****************************************************************/

    // Construtor
    Lexer(int numEstados, int estInicial);
    
    // Destrutor
    ~Lexer();

    /**
     * @brief Configura um estado como final
     * @param numEstado O número do estado
     * @param token Token associado ao estado final
     */
    void configurarEstadoFinal(int numEstado, Token token);

    /**
     * @brief Configura um caractere para ser ignorado na análise
     * @param caractere O caractere que será ignorado
     */
    void configurarCaractereIgnorado(int caractere);

    /**
     * @brief Adiciona uma transição no autômato
     * @param estadoOrigem O estado de origem
     * @param estadoDestino O estado de destino
     * @param charInicio Menor caractere reconhecido na transição
     * @param charFim Maior caractere reconhecido na transição
     */
    void adicionarTransicao(int estadoOrigem, int estadoDestino, int charInicio, int charFim);

    /*****************************************************************
     * MÉTODOS DE ANÁLISE
     *****************************************************************/

    /**
     * @brief Verifica se um estado é válido
     * @param numeroEstado O número do estado a ser analisado
     */
    bool ehEstadoValido(int numeroEstado);

    /**
     * @brief Verifica se um estado é final
     * @param numeroEstado O número do estado a ser analisado
     */
    bool ehEstadoFinal(int numeroEstado);

    /**
     * @brief Verifica se um caractere é válido
     * @param caractere O caractere a ser analisado
     */
    bool ehCaractereValido(int caractere);

    /**
     * @brief Verifica o proximo token da entrada
     * @return O token reconhecido
     */
    Token getNextToken();

    /*****************************************************************
     * MÉTODOS DE EXPORTAÇÃO
     *****************************************************************/

    /**
     * @brief Exporta a matriz de transição para um arquivo .txt
     */
    void exportarMatrizTransicao();
};

#endif