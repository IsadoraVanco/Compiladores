#ifndef _REGALLOC_H_
#define _REGALLOC_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef unsigned int TipoChave;

class Grafo
{
private:
    enum class Resultado{
        SPILL,
        ALLOCATION
    };

    int numeroId;
    int numeroCores;
    std::unordered_map<TipoChave, std::unordered_set<TipoChave>> grafo;
    std::vector<Resultado> analises;

    // Temporários
    std::unordered_set<TipoChave> arestasTemp;

    /**
     * @brief Verifica se as configurações foram definidas
     */
    bool configuracoesEstaoDefinidas();

public:
    // Construtor
    Grafo();

    // Desconstrutor
    ~Grafo();

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
     * @brief Mostra as configurações definidas
     */
    void mostrarConfiguracoes();

    /**
     * @brief Mostra o resultado de cada análise feita 
     */
    void resumirAnalises();
};

extern Grafo *regalloc;

#endif