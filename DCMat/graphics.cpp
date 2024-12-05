#include "graphics.h"
#include <iostream>
#include <cmath>

using std::cout;

/******************************************************
*       TELA
*******************************************************/

void clearScreen(Grafico *graphics)
{
    graphics->deltaX = (graphics->h_view.high - graphics->h_view.low) / LARGURA_TELA;
    graphics->deltaY = (graphics->v_view.high - graphics->v_view.low) / ALTURA_TELA;

    // Limpa com espaços em branco
    int i = 0;
    int j = 0;
    for(i; i < ALTURA_TELA; i++){
        for(j = 0; j < LARGURA_TELA; j++){
            graphics->tela[i][j] = ' ';
        }
    }

    // Se estiver habilitado, coloca os eixos
    if(graphics->draw_axis){
        int y = static_cast<int>((0 - graphics->h_view.low) / graphics->deltaX);
        
        // Eixo y
        if(graphics->h_view.low <= 0 && graphics->h_view.high >= 0){
            int i = 0;

            if(y >= 0 && y < LARGURA_TELA){
                for(i; i < ALTURA_TELA; i++){
                    graphics->tela[i][y] = '|';
                }
            }
        }

        int x = ALTURA_TELA - 1 - static_cast<int>((0 - graphics->v_view.low) / graphics->deltaY);

        // Eixo x
        if(graphics->v_view.low <= 0 && graphics->v_view.high >= 0){
            int i = 0;

            if(x >= 0 && x < ALTURA_TELA){
                for(i; i < LARGURA_TELA; i++){
                    graphics->tela[x][i] = '-';
                }

                // Intersecção dos eixos
                if(y >= 0 && y < LARGURA_TELA){
                    graphics->tela[x][y] = '+';
                }
            }
        }
    }
}

void showScreen(Grafico *graphics)
{
    cout << "\n";
    
    int i = 0;
    int j;
    for(i; i < ALTURA_TELA; i++){
        for(j = 0; j < LARGURA_TELA; j++){
            cout << graphics->tela[i][j];
        }

        cout << "\n";
    }
}

/******************************************************
*       CONTEÚDO
*******************************************************/

void definePoint(Grafico *graphics, double x, double y)
{
    int posicaoX = static_cast<int>(std::round((x - graphics->h_view.low) / graphics->deltaX));
    int posicaoY = ALTURA_TELA - static_cast<int>(std::round((y - graphics->v_view.low) / graphics->deltaY));


    if(posicaoX >= 0 && posicaoX < LARGURA_TELA
        && posicaoY >= 0 && posicaoY < ALTURA_TELA){
        graphics->tela[posicaoY][posicaoX] = '*';
    }
    // cout << "\nponto: " << posicaoX << "," << posicaoY;
}