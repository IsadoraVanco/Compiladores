#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ESTADO_INVALIDO 0
#define ESTADO_INICIAL 1

// Matriz que representa a transição de estados
int estados[][6] = 
{ 
// 0-9, a-d, e, f-z, +, -
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    {5, 2, 2, 2, 3, 4},
    {2, 2, 2, 2, ESTADO_INVALIDO, ESTADO_INVALIDO},
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    {ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    {5, ESTADO_INVALIDO, 6, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    {8, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, 7, 7},
    {8, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO},
    {8, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO, ESTADO_INVALIDO}
};

// Marca os estados finais
int estadosFinais[] = {2, 3, 4, 5, 8};

/**
 * @brief Verifica se é estado final
 */
bool ehEstadoFinal(int estado){
    for(int i = 0; i < 5; i++){
        if(estado == estadosFinais[i]){
            return true;
        }
    }
    return false;
}

/**
 * @brief Mostra uma substring (token)
 */
void mostrarToken(char *string, int inicio, int fim){
    int tamanho = fim - inicio + 1;
    char token[tamanho + 1];

    strncpy(token, &string[inicio], tamanho);
    token[tamanho] = '\0';

    printf("%s\n", token);
}

void analisarEntrada(char *entrada, int tamanho){
    int indiceAtual = 0;
    int indiceInicioToken = 0;
    int indiceFimToken = -1;

    int estadoAtual = ESTADO_INICIAL;
    int proximoEstado = ESTADO_INVALIDO;
    int ultimoEstadoFinal = ESTADO_INVALIDO;

    bool caractereInvalido = false;

    while(indiceInicioToken < tamanho){
        char caractereAtual = entrada[indiceAtual];
        // printf("caractere %c\n", caractereAtual);

        // Analisa os caracteres e atualiza o estado
        if(caractereAtual >= '0' && caractereAtual <= '9'){ // 0 - 9
            proximoEstado = estados[estadoAtual][0];
        }else if(caractereAtual >= 'a' && caractereAtual <= 'd'){ // a-d
            proximoEstado = estados[estadoAtual][1];
        }else if(caractereAtual == 'e'){ // e
            proximoEstado = estados[estadoAtual][2];
        }else if(caractereAtual >= 'f' && caractereAtual <= 'z'){ // f-z
            proximoEstado = estados[estadoAtual][3];
        }else if(caractereAtual == '+'){ // +
            proximoEstado = estados[estadoAtual][4];
        }else if(caractereAtual == '-'){ // -
            proximoEstado = estados[estadoAtual][5];
        }else{ // caractere invalido   
            if(indiceAtual == indiceInicioToken){
                caractereInvalido = true;   
            }
            proximoEstado = ESTADO_INVALIDO;
        }

        // printf("estado %d\n", proximoEstado);

        // Verifica se é inválido
        if(proximoEstado == ESTADO_INVALIDO){
            // printf("inicio %d fim %d\n", indiceInicioToken, indiceFimToken);
            // printf("estado %d indAtual %d\n", proximoEstado, indiceAtual);

            // Verifica se o último token foi definido
            if(indiceFimToken >= indiceInicioToken){
                mostrarToken(entrada, indiceInicioToken, indiceFimToken);
                indiceInicioToken = indiceFimToken + 1;
                indiceFimToken = -1;

                // Passa o indice atual para o inicio do proximo token
                indiceAtual = indiceInicioToken;
            }else{
                // Volta o indice atual para o proximo indice do começo para avaliar
                indiceAtual = indiceInicioToken + 1;
                indiceInicioToken = indiceInicioToken + 1;
            }

            // Verifica se é caractere inválido
            if(caractereInvalido && indiceAtual == indiceInicioToken){
                printf("ERRO\n");
                caractereInvalido = false;
                // indiceAtual++;
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
                    mostrarToken(entrada, indiceInicioToken, indiceFimToken);
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
        
        // Remove o \n
        entrada[strcspn(entrada, "\n")] = '\0';
        analisarEntrada(entrada, strlen(entrada));
    }

    printf("\n-> Obrigada! :)\n");

    return 0;
}