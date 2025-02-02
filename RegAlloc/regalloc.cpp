#include <iostream>
#include "regalloc.h"

using std::cout;
using std::unordered_map;
using std::unordered_set;

// Construtor
RegAlloc::RegAlloc(){
    numeroId = -1;
    numeroCores = -1;
}

// Destrutor
RegAlloc::~RegAlloc(){

}

// *****************************************************************

bool RegAlloc::configuracoesEstaoDefinidas(){
    return numeroId >= 0 && numeroCores >= 0;
}

// *****************************************************************

void RegAlloc::setNumeroId(TipoChave id){
    numeroId = id;
}

void RegAlloc::setNumeroCores(TipoChave cores){
    numeroCores = cores;
    analises.assign(numeroCores, Resultado::SPILL);
}

void RegAlloc::adicionarAresta(TipoChave aresta){
    // cout << "->" << aresta << "\n";
    arestasTemp.insert(aresta);
}

void RegAlloc::adicionarVertice(TipoChave vertice){
    // cout << "V:" << vertice << "\n";

    for(const auto &i : arestasTemp){
        grafo[vertice].insert(i);
        grafo[i].insert(vertice);
    }

    arestasTemp.clear();
}

// *****************************************************************

void RegAlloc::mostrarGrafo(){
    for(const auto& [vertice, vizinhos] : grafo){
        cout << "V: " << vertice << " -> ";
        
        for(const auto& vizinho : vizinhos){
            cout << vizinho << " ";
        }
        
        cout << "\n";
    }
}

// *****************************************************************

void RegAlloc::mostrarConfiguracoes(){
    if(configuracoesEstaoDefinidas()){
        cout << "Graph " << numeroId << " -> ";
        cout << "Physical Registers: " << numeroCores << "\n";
        cout << "----------------------------------------\n";
    }
}

void RegAlloc::avaliarColoracoes(){
    // 
}

void RegAlloc::resumirAnalises(){
    if(configuracoesEstaoDefinidas()){
        cout << "----------------------------------------\n";
        for(int i = analises.size(); i >= 2; i--){
            cout << "Graph " << numeroId << " -> K = " << i;
            cout << ": " << (analises[i] == Resultado::SPILL ? "SPILL" : "Successful Allocation");
            cout << "\n";
        }
    }
}