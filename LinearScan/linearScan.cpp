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

void LinearScan::limparUltimaAlocacao(){
    ativos.clear();
    
    alocacoes.clear();
}

void LinearScan::alocarRegistradores(TipoRegFisico k){
    // Limpa todos os últimos valores
    limparUltimaAlocacao();

    // Inicializa os registradores livres
    bool livres[k];
    for(int i = 0; i < k; i++){
        livres[i] = true;
    }

    // Itera sob a lista ordenada de tempo de vida
    auto it = registradores.begin();
    for(int iteracao = 0; it != registradores.end(); iteracao++){
        
        // Procura um registrador expirado
        for(auto exp = ativos.begin(); exp != ativos.end(); ){
            // cout << "verifica se é expirado: " << *exp << "\n";
            Registrador *regAtual = regIndices[*exp];
            TipoLinha fimAtual = regAtual->fim;
            // cout << "fim " << fimAtual << "\n";

            // Registrador expirado
            if(fimAtual <= it->inicio){  
                TipoRegFisico expirado = alocacoes[*exp];
                livres[expirado] = true;
                // Remove e avança para o próximo
                exp = ativos.erase(exp);
            }else{
                ++exp;
            }
        }

        // Existe um registrador disponivel
        if(ativos.size() < k){
            // cout << "ativos: " << ativos.size() << "\n";
            // Procura o menor registrador disponível
            TipoRegFisico menorReg;
            for(int i = 0; i < k; i++){
                if(livres[i]){
                    menorReg = i;
                    livres[i] = false;
                    break;
                }
            }
            
            // Coloca como ativo
            ativos.push_back(it->id);

            // Marca como registrador alocado
            // cout << "Aloca " << it->id << " em " << menorReg << "\n";
            alocacoes[it->id] = menorReg;
        }else{
            //spill
            alocacoes[it->id] = numeroRegTotais;
            cout << "Spill em " << it->id << " na iteração " << iteracao << "\n";
        }

        ++it;
    }
    // cout << "fim da alocação\n";
}

void LinearScan::mostrarAlocacoes(){
    auto it = registradores.begin();
    while(it != registradores.end()){
        cout << "vr" << it->id << ": ";
        
        if(alocacoes[it->id] >= numeroRegTotais){
            cout << "SPILL";
        }else{
            cout << alocacoes[it->id];
        }
        cout << "\n";
        
        it++;
    }
}

void LinearScan::mostrarSpills(TipoRegFisico k){
    cout << spills.at(k)[0];

    for(int i = 1; i < spills.at(k).size(); i++){
        cout << ", " << spills.at(k)[i];
    }
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