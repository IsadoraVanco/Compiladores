#include <iostream>
#include <cmath>
#include <algorithm>
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

    // Inicializa os registradores ativos
    std::vector<Registrador *> ativos;

    // Itera sob a lista ordenada de tempo de vida
    auto regIt = registradores.begin();
    for(int numIteracao = 0; regIt != registradores.end(); numIteracao++){
        // cout << "====it: " << numIteracao << " linha: " << regIt->inicio << " ====\n";
        // Procura um registrador expirado
        for(auto exp = ativos.begin(); exp != ativos.end(); ){
            TipoLinha fimAtual = (*exp)->fim;

            // Registrador expirado
            if(fimAtual <= regIt->inicio){  
                TipoRegFisico expirado = alocacoes[(*exp)->id];
                livres[expirado] = true;
                // cout << "E: " << expirado << " <-- " << (*exp)->id << "\n";
                // Remove e avança para o próximo
                exp = ativos.erase(exp);
            }else{
                ++exp;
            }
        }

        // Existe um registrador disponivel
        if(ativos.size() < k){
            // Procura o menor registrador disponível
            TipoRegFisico menorReg;
            for(int i = 0; i < k; i++){
                if(livres[i]){
                    menorReg = i;
                    livres[i] = false;
                    // cout << "A: " << i << " --> " << regIt->id << "\n";
                    break;
                }
            }
            
            // Coloca como ativo
            ativos.push_back(&(*regIt));

            // Marca como registrador alocado
            alocacoes[regIt->id] = menorReg;
        }else{
            // Spill
            Registrador *candidatoSpill = &(*regIt);
            // cout << "S: Candidato inicial " << candidatoSpill->id << "\n";

            // Procura se há um registrador ativo melhor para spill
            for(auto ativosIt = ativos.begin(); ativosIt != ativos.end(); ){ 
                
                // Procura o que morre depois
                if((*ativosIt)->fim >= candidatoSpill->fim){
                    candidatoSpill = *ativosIt;
                    // cout << "S: " << (*ativosIt)->id << " morre depois -> " << (*ativosIt)->fim << "\n";

                }else if((*ativosIt)->fim == candidatoSpill->fim){
                    TipoLinha intervaloAtivo = (*ativosIt)->fim - (*ativosIt)->inicio;
                    TipoLinha intervaloCandidato = candidatoSpill->fim - candidatoSpill->inicio;
                    
                    // Procura o que tenha o menor intervalo
                    if(intervaloAtivo < intervaloCandidato){
                        candidatoSpill = *ativosIt;
                        // cout << "S: " << (*ativosIt)->id << " tem menor intervalo -> " << intervaloAtivo << "\n";
                        
                    }else if(intervaloAtivo == intervaloCandidato){
                        // Procura o que foi alocado recentemente
                        if((*ativosIt)->inicio < candidatoSpill->inicio){
                            candidatoSpill = *ativosIt;
                            // cout << "S: " << (*ativosIt)->id << " foi alocado recentemente -> " << (*ativosIt)->fim << "\n";
                        }
                    }
                }
                
                ++ativosIt;
            }

            // Adiciona a iteração que teve spill
            spills[k].push_back(numIteracao);
            analises.at(k - 1) = Resultado::SPILL;

            // Remove dos ativos, caso o novo spill seja um ativo
            auto spillIt = ativos.begin();
            while(spillIt != ativos.end()){
                if((*spillIt)->id == candidatoSpill->id){
                    // Desaloca o espaço e marca como livre
                    TipoRegFisico regSpill = alocacoes[(*spillIt)->id];
                    livres[regSpill] = true;
                    // cout << "S: Libera o reg " << regSpill << "\n";
                    
                    // Retira dos ativos
                    ativos.erase(spillIt);

                    // Volta a iteração
                    if(regIt != registradores.begin()){
                        --regIt;
                    }
                    --numIteracao;

                    break;
                }
                ++spillIt;
            }
            
            // Marca como spill nas alocações
            alocacoes[candidatoSpill->id] = numeroRegTotais;

            // cout << "Spill: escolhido " << candidatoSpill->id << "\n";
            
        }

        // cout << numIteracao << "-Analisado: " << regIt->id << "\n";
        ++regIt;
    }
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
    while(it != registradores.end() && (it->inicio <= inicio)){
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
        cout << "\nK = " << i + 1 << ": ";
        
        if(analises[i] == Resultado::ALLOCATION){
            cout << "Successful Allocation";
        }else{
            cout << "SPILL on interation(s): ";
            mostrarSpills(i + 1);
        }
    }
}