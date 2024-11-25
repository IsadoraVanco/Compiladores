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
    int linhas;  // Quantidade de linhas adicionadas
    int colunas;  // Quantidade de colunas adicionadas
    vector<vector<double>> matriz;  // A matriz dinâmica
}Matriz;

typedef struct {
    Tipo tipo;
    double valor;
    Matriz *matriz;
}Variavel;

#endif