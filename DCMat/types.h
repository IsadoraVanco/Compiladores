#ifndef _TYPES_H_
#define _TYPES_H_

#include <vector>
using std::vector;

enum class Tipo {
    FLOAT,
    MATRIX
};

typedef struct {
    double low;
    double high;
}Limites;

typedef struct {
    int i;
    int j;
    vector<vector<double>> matriz;
}Matriz;

typedef struct {
    Tipo tipo;
    double valor; // Ou tamanho da matriz
    Matriz *matriz;
}Variavel;

#endif