#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "types.h"
#include "ast.h"

#define ALTURA_TELA 25
#define LARGURA_TELA 80

typedef struct grafico {
    char tela[ALTURA_TELA][LARGURA_TELA];
    double deltaX;
    double deltaY;
    
    Limites h_view;
    Limites v_view;
    bool draw_axis;
    bool erase_plot;
    bool connect_dots;
}Grafico;

/******************************************************
*       TELA
*******************************************************/

/**
 * @brief Limpa os gráficos da tela, deixando apenas 
 * os eixos de coordenadas, se habilitados
 */
void clearScreen(Grafico *graphics);

/**
 * @brief Mostra a tela guardada
 * @param graphics O endereço dos gráficos
 */
void showScreen(Grafico *graphics);

/******************************************************
*       CONTEÚDO
*******************************************************/

/**
 * @brief Define o ponto na tela
 * @param graphics O endereço dos gráficos
 * @param x O valor no eixo x
 * @param y O valor no eixo y
 */
void definePoint(Grafico *graphics, double x, double y);

#endif