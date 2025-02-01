#include <iostream>
#include "grafo.h"

using std::cout;
using std::unordered_map;
using std::unordered_set;

// Construtor
Grafo::Grafo(){
    numeroId = -1;
    numeroCores = -1;
}

// Destrutor
Grafo::~Grafo(){

}

// *****************************************************************

bool Grafo::configuracoesEstaoDefinidas(){
    return numeroId >= 0 && numeroCores >= 0;
}

// *****************************************************************

void Grafo::setNumeroId(TipoChave id){
    numeroId = id;
}

void Grafo::setNumeroCores(TipoChave cores){
    numeroCores = cores;
}

void Grafo::adicionarAresta(TipoChave aresta){
    // cout << "->" << aresta << "\n";
    arestasTemp.insert(aresta);
}

void Grafo::adicionarVertice(TipoChave vertice){
    // cout << "V:" << vertice << "\n";

    for(int i = 0; i < arestasTemp.size(); i++){
        grafo[vertice].insert(i);
        grafo[i].insert(vertice);
    }

    arestasTemp.clear();
}

// *****************************************************************

void Grafo::mostrarConfiguracoes(){
    if(configuracoesEstaoDefinidas()){
        cout << "Graph " << numeroId << " -> ";
        cout << "Physical Registers: " << numeroCores << "\n";
        cout << "----------------------------------------\n";
    }
}

void Grafo::resumirAnalises(){
    if(configuracoesEstaoDefinidas()){
        cout << "----------------------------------------\n";
        for(int i = analises.size(); i >= 2; i--){
            cout << "Graph " << numeroId << " -> K = " << numeroCores;
            cout << ": " << (analises[i] == Resultado::SPILL ? "SPILL" : "Successful Allocation");
            cout << "\n";
        }
    }
}