#include <iostream>
#include <cmath>
#include "linearScan.h"

using std::cout;
using std::list;

// Construtor
LinearScan::LinearScan(){
    numeroRegTotais = -1;
}

// Destrutor
LinearScan::~LinearScan(){

}

// *****************************************************************

bool LinearScan::configuracoesEstaoDefinidas(){
    return numeroRegTotais > 0;
}

void LinearScan::alocarRegistradores(TipoRegFisico k){

}

void LinearScan::mostrarAlocacoes(){

}

void LinearScan::mostrarSpills(TipoRegFisico k){
    
}

// *****************************************************************

void LinearScan::setNumeroRegistradores(TipoChave numero){
    numeroRegTotais = numero;
    analises.assign(numeroRegTotais, Resultado::ALLOCATION);
}

void LinearScan::adicionarRegistradorVirtual(TipoChave id, TipoLinha inicio, TipoLinha fim){
    // Caso já exista, substitui
    auto itExistente = regIndices.find(id);
    if(itExistente != regIndices.end()){
        itExistente->second->inicio = inicio;
        itExistente->second->fim = fim;
        return;
    }
    
    // Adiciona ordenado
    auto it = registradores.begin();
    while(it != registradores.end() && 
            (it->inicio < inicio || (it->inicio == inicio && it->fim < fim))){
        ++it;
    }
    it = registradores.insert(it, {id, inicio, fim});

    regIndices[id] = &(*it);
}

// *****************************************************************

void LinearScan::mostrarRegistradores(){
    cout << "===REGISTRADORES===\n";
    for(auto const& reg: registradores){
        cout << "id: " << reg.id << " [" << reg.inicio << "-" << reg.fim << "]\n";
    }
    cout << "===================\n";
}

// *****************************************************************

void LinearScan::fazerAlocacoes(){
    if(!configuracoesEstaoDefinidas()){
        std::cerr << "Não é possível fazer a alocação: configurações não definidas\n";
        return;
    }
    
    // Faz as alocações de K até 2
    for(int k = numeroRegTotais; k >= 2; k--){
        alocarRegistradores(k);
        
        cout << "K = " << k << "\n\n";
        mostrarAlocacoes();
        cout << "----------------------------------------\n";
    }
}

void LinearScan::resumirAnalises(){
    if(!configuracoesEstaoDefinidas()){
        std::cerr << "Não é possível resumir as análises: configurações não definidas\n";
        return;
    }
    
    int digitos = std::log10(numeroRegTotais) + 1;

    cout << "----------------------------------------";
    for(int i = analises.size() - 1; i >= 1; i--){
        cout << "\nK = ";
        
        // Alinha o número
        int espaco = std::log10(i + 1) + 1;
        espaco = digitos - espaco;
        while(espaco > 0){
            cout << " ";
            espaco--;
        }

        cout << i + 1 << ": ";
        if(analises[i] == Resultado::ALLOCATION){
            cout << "Successful Allocation";
        }else{
            cout << "SPILL on interaction(s): ";
            mostrarSpills(i);
        }
    }
}