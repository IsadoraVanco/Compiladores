#ifndef _REGALLOC_H_
#define _REGALLOC_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

class RegAlloc
{
private:
    typedef unsigned int TipoChave; 

    typedef unsigned int TipoCor;

    typedef std::unordered_set<TipoChave> Vizinhos;

    typedef struct vertice{
        TipoChave chave;
        TipoCor cor;
        Vizinhos *vizinhos;
    }Vertice;
    
    enum class Resultado{
        SPILL,
        ALLOCATION
    };

    // *****************************************************************

    int numeroId;
    int numeroCores;
    std::unordered_map<TipoChave, Vertice*> grafo;
    std::vector<Resultado> analises;

    // Coloração
    std::stack<Vertice*> pilhaVertices;

    // Temporários
    Vizinhos *arestasTemp;

    // *****************************************************************

    /**
     * @brief Verifica se as configurações foram definidas
     */
    bool configuracoesEstaoDefinidas();

    /**
     * @brief Encontra o vértice com menor grau no grafo
     * @param k A quantidade de cores disponíveis
     * @return O endereço do vértice
     */
    Vertice *encontrarVerticeMenorGrau(TipoCor k);

    /**
     * @brief Adiciona os vértices na pilha para serem analisados
     * @param k O número de cores disponíveis
     */
    void adicionarVerticesNaPilha(TipoCor k);

    /**
     * @brief Atribui uma cor para os vértices e volta para o grafo
     * @param k 
     */
    void atribuirCores(TipoCor k);

    /**
     * @brief Adiciona os vértices restantes da pilha no grafo
     */
    void adicionarVerticesNoGrafo();

    /**
     * @brief Faz a coloração do grafo
     * @param k O número de cores disponíveis
     */
    void colorirGrafo(TipoCor k);

public:
    // Construtor
    RegAlloc();

    // Desconstrutor
    ~RegAlloc();

    // *****************************************************************

    /**
     * @brief Modifica o número do id do grafo
     * @param id O número do id do grafo
     */
    void setNumeroId(TipoChave id);

    /**
     * @brief Modifica o número de cores totais
     * @param cores O número de cores
     */
    void setNumeroCores(TipoChave cores);

    /**
     * @brief Adiciona um elemento na lista temporaria 
     * de arestas
     * @param aresta A aresta a ser adicionada
     */
    void adicionarAresta(TipoChave aresta);

    /**
     * @brief Adiciona um vértice no grafo
     * @param vertice O vértice a ser adicionado
     */
    void adicionarVertice(TipoChave vertice);

    // *****************************************************************
    
    /**
     * @brief Mostra o grafo construído
     */
    void mostrarGrafo();

    // *****************************************************************

    /**
     * @brief Mostra as configurações definidas
     */
    void mostrarConfiguracoes();

    /**
     * @brief Avalia a alocação usando coloração para 
     * cada K - 1 tentativas
     */
    void avaliarColoracoes();

    /**
     * @brief Mostra o resultado de cada análise feita 
     */
    void resumirAnalises();
};

extern RegAlloc *regalloc;

#endif