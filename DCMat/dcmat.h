#ifndef _DCMAT_H_
#define _DCMAT_H_

#include "types.h"
#include <string>

using std::string;

class DCMat
{
private:
    // Constantes
    double pi = 3.14159265;
    double e = 2.71828182;

    // Configurações do dcmat
    Limites h_view;
    Limites v_view;
    int float_precision;
    int integral_steps;
    bool draw_axis;
    bool erase_plot;
    bool connect_dots;

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
};

extern DCMat *dcmat;
extern Limites *limites;

#endif