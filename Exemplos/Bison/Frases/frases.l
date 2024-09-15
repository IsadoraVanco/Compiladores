%{
// Reconhecedor de palavras com uma tabela de símbolos
#include <iostream>
#include <string>
#include <unordered_map>
#include "frases.tab.h"

#define CONSULTA 0

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

int estadoAtual;
unordered_map<string, int> tabela;

int cadastrar(int tipo, string palavra);
int buscar(string palavra);
%}

%option noyywrap
%option yylineno

%%

\n              estadoAtual = CONSULTA; // No fim da linha, acaba o processo

^adjetivo       estadoAtual = ADJETIVO; // ^ indica inicio da linha
^substantivo    estadoAtual = SUBSTANTIVO;
^interjeicao    estadoAtual = INTERJEICAO;
^conjuncao      estadoAtual = CONJUNCAO;
^preposicao     estadoAtual = PREPOSICAO;
^adverbio       estadoAtual = ADVERBIO;
^artigo         estadoAtual = ARTIGO;
^numeral        estadoAtual = NUMERAL;
^pronome        estadoAtual = PRONOME;
^verbo          estadoAtual = VERBO; 

[a-zA-Z]+ {
    if(estadoAtual != CONSULTA)
    {
        cadastrar(estadoAtual, yytext);
    }
    else
    {
        // cout << "[" << yytext << "]\n"; 
        switch(buscar(yytext))
        {
            case ADJETIVO: return ADJETIVO;
            case SUBSTANTIVO: return SUBSTANTIVO;
            case INTERJEICAO: return INTERJEICAO;
            case CONJUNCAO: return CONJUNCAO;
            case PREPOSICAO: return PREPOSICAO;
            case ADVERBIO: return ADVERBIO;
            case ARTIGO: return ARTIGO;
            case NUMERAL: return NUMERAL;
            case PRONOME: return PRONOME;
            case VERBO: return VERBO;
            default: cout << yytext << ": não reconhecido" << endl; break;
        }
    }
}

.           ;

%%

int cadastrar(int tipo, string palavra)
{
    if(buscar(palavra) != CONSULTA)
    {
        cout << "Palavra já cadastrada: " << palavra << endl;
        return 0;
    }
    else
    {
        tabela.insert({palavra, tipo});
        // cout << "Palavra cadastrada: " << palavra << endl;
        return 1;
    }
}

int buscar(string palavra)
{
    auto posicao = tabela.find(palavra);

    if(posicao == tabela.end())
    {
        return CONSULTA;
    }

    return posicao->second;
}