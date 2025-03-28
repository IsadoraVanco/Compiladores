#ifndef _DCMAT_H_
#define _DCMAT_H_

#include "types.h"
#include "graphics.h"
#include "ast.h"
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

#define PI 3.14159265
#define NUM_EULER 2.71828182

enum class Erro {
    DividedByZero, 
    VariableX, 
    UndefinedSymbol,
    
    NoMatrix, 
    MatrixLimits,
    MatrixFormat
};

class DCMat
{
private:
    // Constantes
    const int maxMatrix = 10;

    // Flags
    bool flagErro;
    bool flagUndefined;
    bool flagInf;
    bool flagChangedAxis;

    // Configurações do dcmat
    int float_precision;
    int integral_steps;
    Grafico graphics;

    // Variáveis e definições
    Matriz *matrix;
    Matriz *matrixTemp;
    int iMatrix;
    int jMatrix;

    Matriz matrixL;
    Matriz matrixU;

    vector<NodeArvore *> functions;

    unordered_map<string, Variavel> symbols;

    // Funções privadas
    /******************************************************
    *       CONFIGURAÇÕES
    *******************************************************/

   /**
    * @brief Mostra uma mensagem de erro
    */
    void showErrorMessage(string message);

    /**
     * @brief Altera o valor das flags de erros
     * @param status O valor das flags
     */
    void setAllErrorFlags(bool status);

    /******************************************************
    *       EXPRESSÕES
    *******************************************************/
    
    /**
     * @brief Calcula o valor de uma árvore de expressão
     * @param root O endereço do nó raiz da árvore
     * @param variableX Indica se valor da variável x deve
     * ser calculado junto
     * @param xValue O valor da variável x
     * @param id Indica se o valor de um id deve ser utilizado
     * @param idName O nome da variável
     * @param idValue O valor do id que deve ser usado
     * @return O valor calculado
     */
    double calculateValue(NodeArvore *root, bool variableX, double xValue, bool id, string idName, double idValue);

   /**
    * @brief Mostra um valor formatado
    * @param value O valor a ser mostrado
    */
    void showValue(double value);

    /**
     * @brief Limpa as funções definidas, mantendo apenas
     * a última salva
     */
    void eraseFunctions();

    /**
     * @brief Calcula os pontos de uma função
     * @param root O endereço da raíz da árvore de expressão
     */
    void calculatePoints(NodeArvore *root);

    
    /******************************************************
    *       MATRIZ
    *******************************************************/
    
    /**
     * @brief Conta a quantidade de dígitos de um número
     * @param number O número a ser analisado
     * @return A quantidade total de dígitos 
     */
    int countDigits(int number);
    
    /**
     * @brief Cria uma nova matrizs
     * @return O endereço da nova matriz
     */
    Matriz* createMatrix();

    /**
     * @brief Redimensiona a quantidade de colunas da matriz
     * @param matriz O endereço da matriz
     * @param columns A quantidade de colunas
     */
    void resizeColumns(Matriz *matriz, int columns);

    /**
     * @brief Redimensiona a quantidade de linhas da matriz
     * @param matriz O endereço da matriz
     * @param rows A quantidade de linhas
     */
    void resizeRows(Matriz *matriz, int rows);

    /**
     * @brief Decompõe a matriz definida em LU
     */
    void luDecomposition();

    /**
     * @brief Calcula o determinante da matriz U
     * @return O valor do determinante
     */
    double calculateDeterminant();

    /******************************************************
    *       SÍMBOLOS E DECLARAÇÕES
    *******************************************************/

    /**
     * @brief Verifica se um símbolo já existe na lista
     * @param name O nome do símbolo
     * @return Se o símbolo existe ou não
     */
    bool symbolExists(string name);

    /**
     * @brief Verifica se a variável X está presente na 
     * árvore da expressão
     * @param root O endereço do nó raíz 
     * @return Se está presente ou não
     */
    bool isXVariablePresent(NodeArvore *root);

public:
    // Construtor
    DCMat();

    // Desconstrutor
    ~DCMat();

    /**
     * @brief Atualiza os valores do view horizontal
     * @param low O limite inferior
     * @param high O limite superior
     */
    void setHView(double low, double high);

    /**
     * @brief Atualiza os valores do view vertical
     * @param low O limite inferior
     * @param high O limite superior
     */
    void setVView(double low, double high);

    /**
     * @brief Atualiza o valor da precisão decimal mostrada
     * @param precision O valor da precisão
     */
    void setFloatPrecision(int precision);

    /**
     * @brief Atualiza o valor do passo para soma da integral
     * @param steps O valor do passo
     */
    void setIntegralSteps(int steps);

    /**
     * @brief Atualiza se os eixos serão desenhados ou não
     * @param state O estado para o atributo
     */
    void setDrawAxis(bool state);

    /**
     * @brief Atualiza se a função será apagada ou não para
     * plotar uma nova função
     * @param state O estado para o atributo
     */
    void setErasePlot(bool state);

    /**
     * @brief Atualiza se os pontos serão conectados 
     * no desenho da função
     * @param state O estado para o atributo
     */
    void setConnectDots(bool state);

    /******************************************************
    *       CONFIGURAÇÕES
    *******************************************************/

    /**
     * @brief Mostra um erro
     * @param error O tipo do erro
     */
    void showError(Erro error);

   /**
    * @brief Mostra sobre o desenvolvedor
    */
    void showAbout();

   /**
    * @brief Mostra os valores das configurações
    */
   void showSettings();

    /**
     * @brief Redefine as configurações padrão
     */
    void resetSettings();

    /******************************************************
    *       EXPRESSÕES
    *******************************************************/

   /**
    * @brief Calcula o valor de um somatório
    * @param root O endereço do nó raiz da árvore
    * @param limits Os valores de limites do somatório
    * @param xVariable Indica se a variável X está presente 
    * como variável
    * @param id O identificador da variável do somatório, caso 
    * a variável X não seja utilizada
    */
    void calculateSum(NodeArvore *root, Limites *limits, bool xVariable, string id);

    /**
     * @brief Calcula o valor de uma integral utilizando 
     * Soma de Riemann
     * @param limits Os valores dos limites
     * @param root O endereço da raíz da árvore
     */
    void calculateIntegral(Limites *limits, NodeArvore *root);

    /**
     * @brief Mostra em formato RPN uma árvore de expressão
     * @param root O endereço do nó raiz da árvore
     */
    void showRpnExpression(NodeArvore *root);

    /**
     * @brief Mostra o valor calculado de uma árvore 
     * de expressão
     * @param root O endereço do nó raiz da árvore
     */
    void showExpression(NodeArvore *root);

    /**
     * @brief Mostra o gráfico de uma função
     * @param root O endereço do nó da raíz da árvore 
     * de expressão
     */
    void plotFunction(NodeArvore *root);

    /******************************************************
    *       MATRIZ
    *******************************************************/

    /**
    * @brief Mostra a matriz definida
    * @param Matriz O endereço da matriz a ser mostrada
    */
    void showMatrix(Matriz *matriz);

    /**
     * @brief Adiciona uma coluna na matriz
     * @param number O número da nova coluna
     */
    void addColumnMatrix(double number);

    /**
     * @brief Adiciona uma linha na matriz
     */
    void addRowMatrix();

    /**
     * @brief Adiciona a matriz temporária na variável de matriz
     */
    void addMatrix();

    /**
     * @brief Resolve o determinante da matriz definida
     * OBS: Deve ser uma matriz quadrada
     */
    void solveDeterminant();

    /**
     * @brief Resolve o sistema linear definido na matriz
     * OBS: Deve ser uma matriz n x (n + 1)
     */
    void solveLinearSystem();

    /******************************************************
    *       SÍMBOLOS E DECLARAÇÕES
    *******************************************************/

    /**
    * @brief Mostra todos os símbolos definidos
    */
    void showAllSymbols();

    /**
    * @brief Mostra o valor de um símbolo definido
    * @param name Nome do símbolo 
    */
    void showSymbol(string name);

    /**
     * @brief Retorna o valor de um simbolo, caso exista
     * @param name O nome do símbolo
     * @return O valor de um símbolo
     */
    double getSymbol(string name);

    /**
     * @brief Adiciona um símbolo do tipo Float na tabela
     * de símbolos
     * @param name O nome do símbolo
     * @param root O endereço da raíz da árvore da expressão
     */
    void addExpressionSymbol(string name, NodeArvore* root);

    /**
     * @brief Adiciona um símbolo na lista
     * @param name O nome do símbolo
     * @param type O tipo do símbolo
     * @param value O valor do símbolo
     */
    void addSymbol(string name, Tipo type, double value);
};

extern DCMat *dcmat;
extern Limites *limites;
extern char *token;
extern NodeArvore *nodeLeitura;
extern bool erroLexico;
extern bool erroSintatico;

#endif