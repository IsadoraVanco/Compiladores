#ifndef _DCMAT_H_
#define _DCMAT_H_

#include "types.h"
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class DCMat
{
private:
    // Constantes
    double pi = 3.14159265;
    double e = 2.71828182;
    int maxMatrix = 10;

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
    vector<vector<double>> matrix;
    unordered_map<string, Variavel> symbols;

public:
    // Construtor
    DCMat();

    // Desconstrutor
    ~DCMat();

    /**
     * @brief Retorna o valor de Pi
     * @return O valor de pi
     */
    double getPi();

    /**
     * @brief Retorna o valor do número de Euler
     * @return O valor de e
     */
    double getNumE();

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
    void showError(string message);

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

    /**
     * @brief Mostra o erro de divisão
     */
   void showDivideError();

    /**
     * @brief Mostra o erro de utilização da variável x
     */
   void showVariableXError();

    /******************************************************
    *       SÍMBOLOS E DECLARAÇÕES
    *******************************************************/

    /**
    * @brief Mostra a matriz definida
    */
    void showMatrix();

    /**
    * @brief Mostra o valor de um símbolo definido
    * @param name Nome do símbolo 
    */
    void showSymbol(string name);

    /**
    * @brief Mostra todos os símbolos definidos
    */
    void showAllSymbols();

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
};

extern DCMat *dcmat;
extern Limites *limites;

#endif