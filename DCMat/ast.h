#ifndef _AST_H_
#define _AST_H_

#include <string>

using std::string;

// Tipo do elemento na árvore
enum class TipoElemento {
    FUNCAO,
    OPERADOR,
    UNARIO,
    IDENTIFICADOR,
    VARIAVEL_X,
    CONSTANTE
};

enum class Funcao {
    SENO,
    COSSENO,
    TANGENTE,
    ABSOLUTO
};

enum class Operador {
    ADICAO,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO,
    RESTO,
    POTENCIA,
    POSITIVO,
    NEGATIVO
};

typedef struct nodeArvore {
    TipoElemento tipo;    
    std::string id;
    double numero;
    struct nodeArvore* esquerda;       
    struct nodeArvore* direita;   
}NodeArvore;

/******************************************************
*       NÓS
*******************************************************/

/**
 * @brief Cria um novo nó
 * @return O endereço do novo nó
 */
NodeArvore *makeNode();

/**
 * @brief Cria um nó com uma função para a árvore junto com um filho
 * @param function A função que será criada
 * @param node O endereço do nó filho
 * @return O endereço do nó criado 
 */
NodeArvore *makeFunctionNode(Funcao function, NodeArvore *node);

/**
 * @brief Cria um nó com um operador para a árvore
 * @param operation O operador que será criado
 * @param leftChild O endereço do nó filho esquerdo
 * @param rightChild O endereço do nó filho direito
 * @return O endereço do nó criado 
 */
NodeArvore *makeOperatorNode(Operador operation, NodeArvore *leftChild, NodeArvore *rightChild);

/**
 * @brief Cria um nó com um operador unário para a árvore
 * @param unary O operador unário que será criado
 * @param node O endereço do nó filho
 * @return O endereço do nó criado 
 */
NodeArvore *makeUnaryNode(Operador unary, NodeArvore *node);

/**
 * @brief Cria um nó com um identificador para a árvore
 * @param id O identificador que será criado
 * @return O endereço do nó criado 
 */
NodeArvore *makeIdNode(string id);

/**
 * @brief Cria um nó com a variavel x para a árvore
 * @param id O identificador que será criado
 * @return O endereço do nó criado 
 */
NodeArvore *makeXNode(string id);

/**
 * @brief Cria um nó com uma constante para a árvore
 * @param constant A constante que será criada
 * @return O endereço do nó criado 
 */
NodeArvore *makeConstantNode(double constant);

/**
 * @brief Exclui todos os nós da árvore
 * @param root O endereço do nó raiz
 */
void freeNodes(NodeArvore *root);

/******************************************************
*       PERCURSO
*******************************************************/

/**
 * @brief Mostra a árvore em pós ordem
 * @param node O endereço do nó raiz
 * @param float_precision A precisão das casas decimais 
 * para constantes
 */
void showPostOrder(NodeArvore *node, int float_precision);

#endif