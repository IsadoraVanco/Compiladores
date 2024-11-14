#ifndef _TYPES_H_
#define _TYPES_H_

enum class Tipo {
    FLOAT,
    MATRIX
};

typedef struct {
    double low;
    double high;
}Limites;

typedef struct {
    int linha;
    double numero;
}NumMatriz;

typedef struct {
    Tipo tipo;
    double valor; // Ou tamanho da matriz
    double **matriz;
}Variavel;

#endif