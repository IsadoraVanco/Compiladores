#ifndef _REGALLOC_H_
#define _REGALLOC_H_

class Grafo
{
private:
    enum {
        SPILL,
        ALLOCATION
    };

    unsigned int numeroId;
    unsigned int numeroCores;

public:
    // Construtor
    Grafo();

    // Desconstrutor
    ~Grafo();

    /**
     * @brief Modifica o número do id do grafo
     * @param id O número do id do grafo
     */
    void setNumeroId(unsigned int id);

    /**
     * @brief Modifica o número de cores totais
     * @param cores O número de cores
     */
    void setNumeroCores(unsigned int cores);

    /**
     * @brief Mostra as configurações definidas
     */
    void mostrarConfiguracoes();
};

extern Grafo *regalloc;

#endif