#ifndef _DCMAT_H_
#define _DCMAT_H_

#include "types.h"
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

#define PI 3.14159265
#define NUM_EULER 2.71828182

enum class Erro {DividedByZero, VariableX};

class DCMat
{
private:
    // Flags
    bool flagErro;

    // Configurações do dcmat
    Limites h_view;
    Limites v_view;
    int float_precision;
    int integral_steps;
    bool draw_axis;
    bool erase_plot;
    bool connect_dots;

    // Variáveis e definições
    Matriz *matrix;
    Matriz *matrixTemp;
    unordered_map<string, Variavel> symbols;

public:
    // Construtor
    DCMat();

    // Desconstrutor
    ~DCMat();

    /**
     * @brief Atualiza os valores do view horizontal
     * @param low O limite inferior
     * @param high O limite superior
     */
    void setHView(double low, double high);

    /**
     * @brief Atualiza os valores do view vertical
     * @param low O limite inferior
     * @param high O limite superior
     */
    void setVView(double low, double high);

    /**
     * @brief Atualiza o valor da precisão decimal mostrada
     * @param precision O valor da precisão
     */
    void setFloatPrecision(int precision);

    /**
     * @brief Atualiza o valor do passo para soma da integral
     * @param steps O valor do passo
     */
    void setIntegralSteps(int steps);

    /**
     * @brief Atualiza se os eixos serão desenhados ou não
     * @param state O estado para o atributo
     */
    void setDrawAxis(bool state);

    /**
     * @brief Atualiza se a função será apagada ou não para
     * plotar uma nova função
     * @param state O estado para o atributo
     */
    void setErasePlot(bool state);

    /**
     * @brief Atualiza se os pontos serão conectados 
     * no desenho da função
     * @param state O estado para o atributo
     */
    void setConnectDots(bool state);

    /******************************************************
    *       CONFIGURAÇÕES
    *******************************************************/

   /**
    * @brief Mostra uma mensagem de erro
    */
    void showErrorMessage(string message);

    /**
     * @brief Mostra um erro
     * @param error O tipo do erro
     */
    void showError(Erro error);

   /**
    * @brief Mostra sobre o desenvolvedor
    */
    void showAbout();

   /**
    * @brief Mostra os valores das configurações
    */
   void showSettings();

    /**
     * @brief Redefine as configurações padrão
     */
    void resetSettings();
    
    /******************************************************
    *       CALCULAR VALORES
    *******************************************************/

   /**
    * @brief Mostra o valor da expressão
    */
   void showValue(double value);

    /******************************************************
    *       MATRIZ
    *******************************************************/

    /**
    * @brief Mostra a matriz definida
    * @param Matriz O endereço da matriz a ser mostrada
    */
    void showMatrix(Matriz *matriz);

    /**
     * @brief Cria uma nova matrizs
     * @return O endereço da nova matriz
     */
    Matriz* createMatrix();

    /**
     * @brief Aumenta o tamanho da matriz quadrada 
     *  em uma unidade
     * @param matrix O endereço da matriz
     */
    void growMatrix(Matriz *matrix);

    /**
     * @brief Adiciona uma coluna na matriz
     * @param number O número da nova coluna
     */
    void addColumnMatrix(double number);

    /**
     * @brief Adiciona uma linha na matriz
     */
    void addRowMatrix();

    /**
     * @brief Adiciona a matriz temporária na variável de matriz
     */
    void addMatrix();

    /******************************************************
    *       SÍMBOLOS E DECLARAÇÕES
    *******************************************************/

    /**
    * @brief Mostra todos os símbolos definidos
    */
    void showAllSymbols();

    /**
    * @brief Mostra o valor de um símbolo definido
    * @param name Nome do símbolo 
    */
    void showSymbol(string name);

    /**
     * @brief Retorna o valor de um simbolo, caso exista
     * @param name O nome do símbolo
     * @return O valor de um símbolo
     */
    double getSymbol(string name);

    /**
     * @brief Adiciona um símbolo na lista
     * @param name O nome do símbolo
     * @param type O tipo do símbolo
     * @param value O valor do símbolo
     */
    void addSymbol(string name, Tipo type, double value);

    /**
     * @brief Verifica se um símbolo já existe na lista
     * @param name O nome do símbolo
     * @return Se o símbolo existe ou não
     */
    bool symbolExists(string name);
};

extern DCMat *dcmat;
extern Limites *limites;

#endif