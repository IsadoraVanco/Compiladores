#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// #include "estado.h"

#define ESTADO_INVALIDO 0
#define ESTADO_INICIAL 1

// Matriz que representa a transição de estados
int estados[][11] = 
{ 
    // 0-9, a-e, f, g-h, i, j-z, ' ', '-', '\n', '.', outro
    // 0
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 1
    {7, 4, 4, 4, 2, 4, 12, 9, ESTADO_INVALIDO, 5, 13},
    // 2
    {4, 4, 3, 4, 4, 4, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 3
    {4, 4, 4, 4, 4, 4, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 4
    {4, 4, 4, 4, 4, 4, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 5
    {6, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 6
    {6, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 7
    {7, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, 8, ESTADO_INVALIDO},
    // 8
    {8, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 9
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, 10, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 10
    {ESTADO_INVALIDO, 10, 10, 10, 10, 10, ESTADO_INVALIDO, ESTADO_INVALIDO, 11, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 11
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 12
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, 12, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    // 13
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO}
};

int estadosFinais[] = {2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13};

/**
 * @brief Verifica se é estado final
 */
bool ehEstadoFinal(int estado){
    int qtdFinais = sizeof(estadosFinais) / sizeof(int);

    for(int i = 0; i < qtdFinais; i++){
        if(estado == estadosFinais[i]){
            return true;
        }
    }
    return false;
}

/**
 * @brief Mostra uma substring e seu respectivo token
 */
void mostrarToken(char *string, int inicio, int fim, int token){
    int tamanho = fim - inicio + 1;
    char subString[tamanho + 1];

    strncpy(subString, &string[inicio], tamanho);
    subString[tamanho] = '\0';

    char strToken[20];

    switch(token){
    case 2:
        strcpy(strToken, "ID");
        break;
    case 3:
        strcpy(strToken, "IF");
        break;
    case 4:
        strcpy(strToken, "ID");
        break;
    case 5:
        strcpy(strToken, "error");
        break;
    case 6:
        strcpy(strToken, "REAL");
        break;
    case 7:
        strcpy(strToken, "NUM");
        break;
    case 8:
        strcpy(strToken, "REAL");
        break;
    case 9:
        strcpy(strToken, "error");
        break;
    case 11:
        strcpy(strToken, "comment");
        // Retira o '\n'
        subString[tamanho - 2] = '\0';
        break;
    case 12:
        printf("white space\n");
        return;
    case 13:
        strcpy(strToken, "error");
        break;
    
    default:
        break;
    }

    printf("%s %s\n", subString, strToken);
}

/**
 * @brief Analisa e classifica uma entrada lida
 */
void analisarEntrada(char *entrada, int tamanho){
    int indiceAtual = 0;
    int indiceInicioToken = 0;
    int indiceFimToken = -1;

    int estadoAtual = ESTADO_INICIAL;
    int proximoEstado = ESTADO_INVALIDO;
    int ultimoEstadoFinal = ESTADO_INVALIDO;

    while(indiceInicioToken < tamanho){
        char caractereAtual = entrada[indiceAtual];
        // printf("caractere '%c'\n", caractereAtual);

        // Analisa os caracteres e atualiza o estado
        if(caractereAtual >= '0' && caractereAtual <= '9'){ // 0 - 9
            proximoEstado = estados[estadoAtual][0];
        }else if(caractereAtual >= 'a' && caractereAtual <= 'e'){ // a-e
            proximoEstado = estados[estadoAtual][1];
        }else if(caractereAtual == 'f'){ // f
            proximoEstado = estados[estadoAtual][2];
        }else if(caractereAtual >= 'g' && caractereAtual <= 'h'){ // g-h
            proximoEstado = estados[estadoAtual][3];
        }else if(caractereAtual == 'i'){ // i
            proximoEstado = estados[estadoAtual][4];
        }else if(caractereAtual >= 'j' && caractereAtual <= 'z'){ // j-z
            proximoEstado = estados[estadoAtual][5];
        }else if(caractereAtual == ' '){ // ' '
            proximoEstado = estados[estadoAtual][6];
        }else if(caractereAtual == '-'){ // -
            proximoEstado = estados[estadoAtual][7];
        }else if(caractereAtual == '\n'){ // '\n'
            proximoEstado = estados[estadoAtual][8];
        }else if(caractereAtual == '.'){ // .
            proximoEstado = estados[estadoAtual][9];
        }else{ // outro  
            proximoEstado = estados[estadoAtual][10];
        }

        // printf("estado %d\n", proximoEstado);

        // Verifica se é inválido
        if(proximoEstado == ESTADO_INVALIDO){
            // printf("inicio %d fim %d\n", indiceInicioToken, indiceFimToken);
            // printf("estado %d indAtual %d\n", proximoEstado, indiceAtual);

            // Verifica se o último token foi definido
            if(indiceFimToken >= indiceInicioToken){
                mostrarToken(entrada, indiceInicioToken, indiceFimToken, ultimoEstadoFinal);
                indiceInicioToken = indiceFimToken + 1;
                indiceFimToken = -1;

                // Passa o indice atual para o inicio do proximo token
                indiceAtual = indiceInicioToken;
            }else{
                // Volta o indice atual para o proximo indice do começo para avaliar
                indiceAtual = indiceInicioToken + 1;
                indiceInicioToken = indiceInicioToken + 1;
            }

            // Volta para o estado inicial
            estadoAtual = ESTADO_INICIAL;
        }else{
            // Marca se é final
            if(ehEstadoFinal(proximoEstado)){
                ultimoEstadoFinal = proximoEstado;
                indiceFimToken = indiceAtual;
            }
            
            // Ultimo token
            if(indiceAtual >= tamanho - 1){
                if(indiceFimToken >= indiceInicioToken){
                    mostrarToken(entrada, indiceInicioToken, indiceFimToken, ultimoEstadoFinal);
                    estadoAtual = ESTADO_INICIAL;
                }

                indiceInicioToken = indiceFimToken + 1;

                if(indiceInicioToken < indiceAtual){
                    indiceAtual = indiceInicioToken;
                }
            }else{
                indiceAtual++;
                estadoAtual = proximoEstado;
            }
        }
    }
    
}

int main(int argc, char const *argv[])
{
    char entrada[200];

    while(true){
        printf("=>");

        // ctrl + z (windows) e ctrl + d (linux)
        if(fgets(entrada, sizeof(entrada), stdin) == NULL){
            break;
        }
        
        analisarEntrada(entrada, strlen(entrada));
    }

    printf("\n-> Obrigada! :)\n");
    
    return 0;
}