#include "lexer.h"

// Para a entrada e saída de dados padrão
#include <iostream>
// Para manipulação de string
#include <sstream>
// Para a exportação de dados
#include <fstream>

/*****************************************************************
 * DEFINIÇÕES
 *****************************************************************/

// Caractere máximo para reconhecer
#define MAX_CHAR 256

/*
Estado para um caractere desconhecido
(emite erros)
*/
#define ESTADO_DESCONHECIDO -2
/*
Estado de um caractere que não faz parte do token
(não emite erro)
*/
#define ESTADO_DESCONSIDERADO -1
/*
Estado para uma transição invalida de um caractere conhecido
(emite erros, separa os tokens)
*/
#define ESTADO_INVALIDO 0

// Indica se é estado final
#define ESTADO_FINAL 1

/*****************************************************************
 * MÉTODOS PARA LOGS E SAÍDA DE DADOS
 *****************************************************************/

void Lexer::emitirErro(std::string erro)
{
    std::cerr << "[Lexer][ERRO] " << erro << std::endl;
}

/*****************************************************************
 * MÉTODOS DE CONFIGURAÇÃO
 *****************************************************************/

Lexer::Lexer(int numEstados, int estInicial)
{
    if (numEstados <= 0)
    {
        emitirErro("Número de estados insuficiente: " + numEstados);
        return;
    }

    if (estadoInicial < 0 || estadoInicial > numEstados || estadoInicial == ESTADO_INVALIDO)
    {
        emitirErro("Não é possível definir o estado inicial como: " + estadoInicial);
        return;
    }

    int i, j;

    numeroEstados = numEstados;
    estadoInicial = estInicial;

    // Contando com o estado inválido
    int totalEstados = numEstados + 1;

    // Preenche os estados finais
    estadosFinais = new int[totalEstados];
    tokens = new Token[totalEstados];

    for (i = 0; i < totalEstados; i++)
    {
        estadosFinais[i] = ESTADO_INVALIDO;
        tokens[i] = Token::DESCONHECIDO;
    }

    // Preenche a matriz de transição [totalEstados][MAX_CHAR]
    matrizTransicao = new int *[totalEstados];

    for (i = 0; i < totalEstados; i++)
    {
        matrizTransicao[i] = new int[MAX_CHAR + 1];

        for (j = 0; j <= MAX_CHAR; j++)
        {
            matrizTransicao[i][j] = ESTADO_DESCONHECIDO;
        }
    }

    // printf("OK\n");
}

Lexer::~Lexer()
{
    delete estadosFinais;
    delete tokens;

    int i;
    for (i = 0; i <= numeroEstados; i++)
    {
        delete matrizTransicao[i];
    }
    delete matrizTransicao;
}

void Lexer::configurarEstadoFinal(int numEstado, Token token)
{
    if (!ehEstadoValido(numEstado))
    {
        emitirErro("Não é possível configurar o estado como final: " + numEstado);
        return;
    }

    estadosFinais[numEstado] = ESTADO_FINAL;
    tokens[numEstado] = token;
}

void Lexer::configurarCaractereIgnorado(int caractere)
{
    int i;
    for (i = 0; i <= numeroEstados; i++)
    {
        matrizTransicao[i][caractere] = ESTADO_DESCONSIDERADO;
    }
}

void Lexer::adicionarTransicao(int estadoOrigem, int estadoDestino, int charInicio, int charFim)
{
    if (!ehEstadoValido(estadoOrigem))
    {
        emitirErro("Não é possível adicionar uma transição do estado de origem: " + estadoOrigem);
        return;
    }

    if (!ehEstadoValido(estadoDestino))
    {
        emitirErro("Não é possível adicionar uma transição para estado de destino: " + estadoDestino);
        return;
    }

    if (!ehCaractereValido(charInicio) || !ehCaractereValido(charFim))
    {
        std::stringstream erro;
        erro << "Não é possível adicionar uma transição para os caracteres: " << charInicio << " " << charFim << std::endl;
        emitirErro(erro.str());
        return;
    }

    int i, estado;
    // Percorre as colunas dos caracteres
    for (i = charInicio; i <= charFim; i++)
    {
        // Percorre por cada estado
        for (estado = 0; estado <= numeroEstados; estado++)
        {
            // Muda para um estado invalido
            if (matrizTransicao[estado][i] == ESTADO_DESCONHECIDO)
            {
                matrizTransicao[estado][i] = ESTADO_INVALIDO;
            }
        }
        matrizTransicao[estadoOrigem][i] = estadoDestino;
    }
}

/*****************************************************************
 * MÉTODOS DE ANÁLISE
 *****************************************************************/

bool Lexer::ehEstadoValido(int numeroEstado)
{
    return numeroEstado >= 0 && numeroEstado <= numeroEstados && numeroEstado != ESTADO_INVALIDO;
}

bool Lexer::ehEstadoFinal(int numeroEstado)
{
    return estadosFinais[numeroEstado] == ESTADO_FINAL;
}

bool Lexer::ehCaractereValido(int caractere)
{
    return caractere <= MAX_CHAR && caractere >= 0;
}

Token Lexer::getNextToken()
{
    // Continua de onde parou
    int indiceAtual = numeroColuna;
    int indiceInicioToken = numeroColuna;
    int indiceFimToken = -1;

    // Indice da linha carregada
    int numLinhaCarregada = 0;
    int tamanhoEntrada = entradas.at(numLinhaCarregada).length();

    int estadoAtual = estadoInicial;
    int proximoEstado = ESTADO_INVALIDO;
    int ultimoEstadoFinal = ESTADO_INVALIDO;

    bool tokenReconhecido = false;

    while (!entradas.empty() && !tokenReconhecido)
    {
        // Verifica se é o último caractere
        if (indiceAtual >= tamanhoEntrada)
        {
            // Caso precise de mais caracteres, carrega uma nova linha
        }
        else
        {
            // Lê o próximo caractere
            int caractereAtual = (int)entradas.at(numLinhaCarregada)[indiceAtual];
            proximoEstado = matrizTransicao[estadoAtual][caractereAtual];

            if (proximoEstado == ESTADO_INVALIDO || proximoEstado == ESTADO_DESCONHECIDO || proximoEstado == ESTADO_DESCONSIDERADO)
            {
                // Verifica se o último token foi definido
                if (indiceFimToken >= indiceInicioToken)
                {
                    // Verifica se alguma linha foi lida por completo
                    // Caso sim, a tira da lista 

                    tokenReconhecido = true;
                }
                else
                {
                    // Volta o indice atual para o proximo indice do começo para avaliar
                    // Emite um erro
                }

                // Atualiza o indice da coluna lida

                // Volta para o estado inicial
                // estadoAtual = estadoInicial;
            }
            else
            {
                if (ehEstadoFinal(proximoEstado))
                {
                    ultimoEstadoFinal = proximoEstado;
                    indiceFimToken = indiceAtual;
                }

                indiceAtual++;
                estadoAtual = proximoEstado;
            }
        }
    }

    // Retorna o token
}

/*****************************************************************
 * MÉTODOS DE EXPORTAÇÃO
 *****************************************************************/

void Lexer::exportarMatrizTransicao()
{
    if (matrizTransicao == nullptr)
    {
        emitirErro("Matriz de transição não definida para exportação");
        return;
    }

    std::ofstream arquivo;

    arquivo.open("matrizTransicao.txt");

    // Preenche o arquivo
    if (arquivo.is_open())
    {
        int i, j;
        for (i = 0; i <= numeroEstados; i++)
        {
            for (j = 0; j <= MAX_CHAR; j++)
            {
                arquivo << matrizTransicao[i][j] << " ";
            }
            arquivo << "\n";
        }

        arquivo.close();
    }
    else
    {
        emitirErro("Falha ao exportar matriz de transição");
    }
}