#ifndef _DCMAT_H_
#define _DCMAT_H_

#include <string>

using std::string;

class DCMat
{
private:
    // Constantes
    double pi = 3.14159265;
    double e = 2.71828182;

    // Configurações do dcmat
    double h_view_lo;
    double h_view_hi;
    double v_view_lo;
    double v_view_hi;
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

    /******************************************************
    *       CONFIGURAÇÕES
    *******************************************************/

   /**
    * @brief Mostra uma mensagem de erro
    */
    void showError(string message);

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

#endif