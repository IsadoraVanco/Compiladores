#include <iostream>
#include <cmath>
#include "regalloc.h"

using std::cout;
using std::unordered_map;
using std::unordered_set;

// Construtor
RegAlloc::RegAlloc(){
    numeroId = -1;
    numeroCores = -1;
    arestasTemp = new Vizinhos();
}

// Destrutor
RegAlloc::~RegAlloc(){
    delete arestasTemp;

    for(const auto& i: grafo){
        delete i.second->vizinhos;
        delete i.second;
    }

    for(int i = pilhaVertices.size() - 1; i >= 0; i--){
        delete pilhaVertices.top()->vizinhos;
        delete pilhaVertices.top();
    }
}

// *****************************************************************

bool RegAlloc::configuracoesEstaoDefinidas(){
    return numeroId >= 0 && numeroCores >= 0;
}

bool RegAlloc::existeRegistradorVirtual(){
    for(const auto& par: grafo){
        if(par.second->chave >= numeroCores){
            return true;
        }
    }
    return false;
}

RegAlloc::Vertice *RegAlloc::retornarPrimeiroRegVirtual(){
    for(const auto& par: grafo){
        if(par.second->chave >= numeroCores){
            return par.second;
        }
    }

    return nullptr;
}

RegAlloc::Vertice *RegAlloc::encontrarVerticeMenorGrau(TipoCor k){
    Vertice *regVirtual = retornarPrimeiroRegVirtual();

    TipoChave menorChave = regVirtual->chave;
    TipoCor menorGrau = regVirtual->vizinhos ? regVirtual->vizinhos->size() : 0;

    // cout << "== ENCONTRA O MENOR ==\n";
    for(const auto& par: grafo){
        TipoChave chaveAtual = par.first;
        Vertice* verticeAtual = par.second;
        TipoCor grauAtual = verticeAtual->vizinhos ? verticeAtual->vizinhos->size() : 0;

        // cout << "\n a: " << chaveAtual << " [" << grauAtual << "] ";
        // Ignora os vértices de registradores reais
        if(chaveAtual < numeroCores){
            continue;
        }

        // Atualiza se encontrar um vértice com grau menor
        if(grauAtual < menorGrau){
            menorChave = chaveAtual;
            menorGrau = grauAtual;
        }else if(grauAtual == menorGrau && chaveAtual < menorChave){
            menorChave = chaveAtual;
        }
        // cout << "\n-- " << menorGrau << "[" << menorChave << "] ";
    }
    // cout << "\n";

    // Verifica se o menor é menor que K
    if(menorGrau >= k){
        menorChave = regVirtual->chave;
        TipoCor maiorGrau = regVirtual->vizinhos ? regVirtual->vizinhos->size() : 0;
        
        // cout << "== AGORA ENCONTRA O MAIOR ==\n";
        for(const auto& par: grafo){
            TipoChave chaveAtual = par.first;
            Vertice* verticeAtual = par.second;
            TipoCor grauAtual = verticeAtual->vizinhos ? verticeAtual->vizinhos->size() : 0;

            // cout << "\n a: " << chaveAtual << " [" << grauAtual << "] ";
            // Ignora se é um registrador real
            if(chaveAtual < numeroCores){
                continue;
            }

            // Atualiza se encontrar um vértice com grau menor
            if(grauAtual > maiorGrau){
                menorChave = chaveAtual;
                maiorGrau = grauAtual;
            }else if(grauAtual == maiorGrau && chaveAtual < menorChave){
                menorChave = chaveAtual;
            }
            // cout << "\n-- " << menorChave << "[" << maiorGrau << "] ";
        }
        // cout << "\n";
    }

    return grafo[menorChave];
}

void RegAlloc::adicionarVerticesNaPilha(TipoCor k){
    std::vector<TipoChave> menores;

    // Retira os regisradores virtuais
    while(existeRegistradorVirtual()){
        // Procura o vértice que vai ser retirado 
        Vertice *vertice = encontrarVerticeMenorGrau(k);

        // Retira o vértice dos vizinhos
        for(const auto& vizinho: *(vertice->vizinhos)){
            grafo[vizinho]->vizinhos->erase(vertice->chave);
        }

        // Marca se é possível spill
        bool spill = false;
        if(vertice->vizinhos->size() >= k){
            spill = true;
        }

        pilhaVertices.push(vertice);
        grafo.erase(vertice->chave);

        cout << "Push: " << vertice->chave;
        cout << (spill ? " *" : "") << "\n";
        // cout << " => " << vertice->vizinhos->size() << "\n";
    }
}

void RegAlloc::atribuirCores(TipoCor k){
    while(!pilhaVertices.empty()){
        Vertice* vertice = pilhaVertices.top();
        pilhaVertices.pop();

        // Volta o nó para o grafo
        grafo[vertice->chave] = vertice;

        // Adiciona a aresta nos vizinhos
        for(const auto& vizinho: *(vertice->vizinhos)){
            if(grafo.count(vizinho)){
                grafo[vizinho]->vizinhos->insert(vertice->chave);
            }
        }

        // Escolhe uma cor disponível
        std::unordered_set<TipoCor> coresVizinhos;
        for(const auto& vizinho: *(vertice->vizinhos)){
            if(grafo[vizinho]){
                coresVizinhos.insert(grafo[vizinho]->cor);
            }
        }

        // Encontra a menor cor não utilizada pelos vizinhos
        TipoCor novaCor = 0;
        while(coresVizinhos.count(novaCor)){
            novaCor++;
        }

        vertice->cor = novaCor;

        std::cout << "Pop: " << vertice->chave << " -> ";

        if(vertice->cor < k){
            std::cout << vertice->cor << "\n";
        }else{
            std::cout << "NO COLOR AVAILABLE\n";
            analises[k - 1] = Resultado::SPILL;
            
            // Adiciona os vértices restantes no grafo
            while(!pilhaVertices.empty()){
                Vertice* vertice = pilhaVertices.top();
                pilhaVertices.pop();

                // Volta o nó para o grafo
                grafo[vertice->chave] = vertice;

                // Adiciona a aresta nos vizinhos
                for(const auto& vizinho: *(vertice->vizinhos)){
                    if(grafo.count(vizinho)){
                        grafo[vizinho]->vizinhos->insert(vertice->chave);
                    }
                }
            }
        }
    }
}

void RegAlloc::colorirGrafo(TipoCor k){
    cout << "----------------------------------------\n";
    cout << "K = " << k << "\n\n";

    // Adiciona os vértices na pilha
    adicionarVerticesNaPilha(k);
    // mostrarGrafo();

    // Tira da pilha e atribui uma cor
    atribuirCores(k);
    // mostrarGrafo();
}

// *****************************************************************

void RegAlloc::setNumeroId(TipoChave id){
    numeroId = id;
}

void RegAlloc::setNumeroCores(TipoChave cores){
    numeroCores = cores;
    analises.assign(numeroCores, Resultado::ALLOCATION);
}

void RegAlloc::adicionarAresta(TipoChave aresta){
    // cout << "->" << aresta << "\n";
    arestasTemp->insert(aresta);
}

void RegAlloc::adicionarVertice(TipoChave vertice){
    // cout << "V:" << vertice << "\n";

    // Adiciona o vértice e os vizinhos no grafo
    if(!grafo.count(vertice)){
        // cout << "\nVertice não existe " << vertice;
        Vertice *novo = new Vertice();
        novo->chave = vertice;
        novo->vizinhos = arestasTemp;
        arestasTemp = new Vizinhos();

        // Caso seja um registrador físico
        if(vertice < numeroCores){
            novo->cor = vertice;
        }else{
            novo->cor = numeroCores;
        }

        grafo[vertice] = novo;
    }else{
        // cout << "\nVertice existe " << vertice << "\n";

        // Verifica quais vizinhos faltam
        for(const auto& vizinho: *arestasTemp){
            grafo[vertice]->vizinhos->insert(vizinho);
        }
    }

    // Adiciona os vizinhos
    for(const auto& vizinho: *arestasTemp){
        // Verifica se existe o vértice do vizinho no grafo
        if(grafo.count(vizinho)){
            // cout << "Vizinho existe " << vizinho << "\n";
            grafo[vizinho]->vizinhos->insert(vertice);
        }else{
            // cout << "\nVizinho não existe " << vizinho;
            Vertice *novoVizinho = new Vertice(); 
            novoVizinho->chave = vizinho;
            // Se é um registrador físico
            if(vizinho < numeroCores){
                novoVizinho->cor = vizinho;
            }else{
                novoVizinho->cor = numeroCores;
            }

            novoVizinho->vizinhos = new Vizinhos();
            novoVizinho->vizinhos->insert(vertice);

            grafo[vizinho] = novoVizinho;
        }
    }
}

// *****************************************************************

void RegAlloc::mostrarGrafo(){
    cout << "== GRAFO ==\n";
    for(const auto& par : grafo){
        TipoChave vertice = par.first;
        Vertice* v = par.second;

        cout << "Vértice " << vertice << " -> ";

        for(const auto& vizinho: *(v->vizinhos)){
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
    if(configuracoesEstaoDefinidas()){
        for(int i = numeroCores; i >= 2; i--){
            colorirGrafo(i);
        }

        cout << "----------------------------------------\n";
    }
}

void RegAlloc::resumirAnalises(){
    if(configuracoesEstaoDefinidas()){
        int digitos = std::log10(numeroCores) + 1;

        cout << "----------------------------------------";
        for(int i = analises.size() - 1; i >= 1; i--){
            cout << "\nGraph " << numeroId << " -> K = ";
            
            // Alinha o número
            int espaco = std::log10(i + 1) + 1;
            espaco = digitos - espaco;
            while(espaco > 0){
                cout << " ";
                espaco--;
            }

            cout << i + 1 << ": ";
            cout << (analises[i] == Resultado::SPILL ? "SPILL" : "Successful Allocation");
        }
    }
}