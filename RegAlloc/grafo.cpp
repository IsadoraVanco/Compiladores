#include <iostream>
#include "grafo.h"

using std::cout;

Grafo::Grafo(){

}

Grafo::~Grafo(){

}

void Grafo::mostrarConfiguracoes(){
    cout << "Graph " << numeroId << " -> ";
    cout << "Physical Registers: " << numeroCores << "\n";
    cout << "----------------------------------------\n";
}

void Grafo::setNumeroId(unsigned int id){
    numeroId = id;
}

void Grafo::setNumeroCores(unsigned int cores){
    numeroCores = cores;
}