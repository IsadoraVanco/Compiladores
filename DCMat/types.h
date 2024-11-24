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
    int i;  // Quantidade de linhas adicionadas
    int j;  // Quantidade de colunas adicionadas
    int tamanho;    // O tamanho da matriz
    vector<vector<double>> matriz;  // A matriz dinâmica
}Matriz;

typedef struct {
    Tipo tipo;
    double valor; // Ou tamanho da matriz
    Matriz *matriz;
}Variavel;

#endif