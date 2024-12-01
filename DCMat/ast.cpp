#include <iostream>
#include <iomanip>
#include "ast.h"

using std::cout;

/******************************************************
*       NÓS
*******************************************************/

NodeArvore *makeNode()
{
    NodeArvore *novo = new NodeArvore;
    novo->direita = NULL;
    novo->esquerda = NULL;
    novo->id = "";
    novo->numero = 0;
    novo->tipo = TipoElemento::CONSTANTE;

    // cout << "nó criado!\n";
    return novo;
}

NodeArvore *makeFunctionNode(Funcao function, NodeArvore *node)
{
    NodeArvore *novo = makeNode();
    novo->tipo = TipoElemento::FUNCAO;
    novo->esquerda = node;

    switch(function)
    {
    case Funcao::SENO:
        novo->id = "SEN";
        break;

    case Funcao::COSSENO:
        novo->id = "COS";
        break;

    case Funcao::TANGENTE:
        novo->id = "TAN";
        break;
    
    case Funcao::ABSOLUTO:
        novo->id = "ABS";
        break;
    
    default:
        break;
    }

    return novo;
}

NodeArvore *makeOperatorNode(Operador operation, NodeArvore *leftChild, NodeArvore *rightChild)
{
    NodeArvore *novo = makeNode();
    novo->tipo = TipoElemento::OPERADOR;
    novo->esquerda = leftChild;
    novo->direita = rightChild;

    switch(operation)
    {
    case Operador::ADICAO:
        novo->id = "+";
        break;

    case Operador::SUBTRACAO:
        novo->id = "-";
        break;

    case Operador::MULTIPLICACAO:
        novo->id = "*";
        break;

    case Operador::DIVISAO:
        novo->id = "/";
        break;

    case Operador::RESTO:
        novo->id = "%";
        break;

    case Operador::POTENCIA:
        novo->id = "^";
        break;
    
    default:
        break;
    }

    return novo;
}

NodeArvore *makeUnaryNode(Operador unary, NodeArvore *node)
{
    NodeArvore *novo = makeNode();
    novo->tipo = TipoElemento::UNARIO;
    novo->esquerda = node;

    switch (unary)
    {
    case Operador::POSITIVO:
        novo->id = "+";
        break;

    case Operador::NEGATIVO:
        novo->id = "-";
        break;
    
    default:
        break;
    }

    return novo;
}

NodeArvore *makeIdNode(string id)
{
    NodeArvore *novo = makeNode();
    novo->tipo = TipoElemento::IDENTIFICADOR;
    novo->id = id;

    return novo;

}

NodeArvore *makeXNode(string id)
{
    NodeArvore *novo = makeNode();
    novo->tipo = TipoElemento::VARIAVEL_X;
    novo->id = id;

    return novo;
}

NodeArvore *makeConstantNode(double constant)
{
    NodeArvore *novo = makeNode();
    novo->tipo = TipoElemento::CONSTANTE;
    novo->numero = constant;
    return novo;
}

void freeNodes(NodeArvore *root)
{
    if(!root){
        return;
    }

    if(root->esquerda != NULL){
        freeNodes(root->esquerda);
    }

    if(root->direita != NULL){
        freeNodes(root->direita);
    }

    delete root;
}

/******************************************************
*       PERCURSO
*******************************************************/

void showPostOrder(NodeArvore *node, int float_precision)
{
    if(!node){
        return;
    }

    if(node->esquerda != NULL){
        // cout << "esq\n";
        showPostOrder(node->esquerda, float_precision);
    }

    if(node->direita != NULL){
        // cout << "dir\n";
        showPostOrder(node->direita, float_precision);
    }

    switch (node->tipo)
    {
    case TipoElemento::FUNCAO:
    case TipoElemento::OPERADOR:
    case TipoElemento::UNARIO:
    case TipoElemento::IDENTIFICADOR:
    case TipoElemento::VARIAVEL_X:
        cout << node->id << " ";
        break;

    case TipoElemento::CONSTANTE:
        cout << std::fixed << std::setprecision(float_precision) << node->numero << " ";
        break;
    
    default:
        break;
    }
}