#ifndef _LINEARSCAN_H_
#define _LINEARSCAN_H_

#include <unordered_map>
#include <vector>
#include <list>

class LinearScan
{
private: 
    // Representa a chave do registrador virtual
    typedef unsigned int TipoChave;
    // Representa o número da linha do programa
    typedef unsigned int TipoLinha;
    // Representa o número do registrador físico
    typedef unsigned int TipoRegFisico;
    // Representa o número da iteração
    typedef unsigned int TipoIteracao;

    typedef struct reg{
        TipoChave id;
        TipoLinha inicio;
        TipoLinha fim;
    }Registrador;

    enum class Resultado{
        SPILL,
        ALLOCATION
    };

    // *****************************************************************
    
    int numeroRegTotais;
    std::list<Registrador> registradores;
    std::unordered_map<TipoChave, TipoRegFisico> alocacoes;
    std::vector<TipoChave> ativos;
    std::vector<Resultado> analises;

    // Spill
    std::unordered_map<TipoRegFisico, std::vector<TipoIteracao>> spills;
    
    // Auxiliar 
    std::unordered_map<TipoChave, Registrador*> regIndices;
    
    // *****************************************************************

    /**
     * @brief Verifica se as configurações foram definidas
     */
    bool configuracoesEstaoDefinidas();
    
    /**
     * @brief Limpa todos os valores obtidos na última alocação
     */
    void limparUltimaAlocacao();

    /**
     * @brief Faz a alocação dos registradores de acordo com o
     * total disponível
     * @param k O número total de registradores disponíveis
     */
    void alocarRegistradores(TipoRegFisico k);

    /**
     * @brief Mostra as alocações feitas na última alocação
     */
    void mostrarAlocacoes();

    /**
     * @brief Mostra as iterações que teve spill
     * @param k A quantidade total de registradores disponíveis
     */
    void mostrarSpills(TipoRegFisico k);

public:
    // Construtor
    LinearScan();

    // Desconstrutor
    ~LinearScan();

    // *****************************************************************

    /**
     * @brief Modifica o número de registradores físicos totais
     * @param numero O número de registradores físicos
     */
    void setNumeroRegistradores(TipoChave numero);

    /**
     * @brief Adiciona um registrador com seu id e indicando seu 
     * tempo de vida
     * @param id O id do registrador virtual
     * @param inicio A linha que o registrador é declarado
     * @param fim A última linha que tem referência ao registrador
     */
    void adicionarRegistradorVirtual(TipoChave id, TipoLinha inicio, TipoLinha fim);

    // *****************************************************************
    
    /**
     * @brief Mostra os registradores armazenados
     */
    void mostrarRegistradores();

    // *****************************************************************

    /**
     * @brief Faz as alocações usando o algoritmo do Linear Scan 
     * para cada K - 1 tentativas
     */
    void fazerAlocacoes();

    /**
     * @brief Mostra o resultado de cada análise feita 
     */
    void resumirAnalises();
};

extern LinearScan *linearScan;

#endif