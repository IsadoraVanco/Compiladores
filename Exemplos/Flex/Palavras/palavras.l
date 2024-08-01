%{
// Reconhecedor de palavras com uma tabela de símbolos
#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

enum {
    // Está consultando ao invés de cadastrar
    CONSULTA = 0,

    // Classificações possíveis
    DESCONHECIDO,
    ADJETIVO,
    SUBSTANTIVO,
    INTERJEICAO,
    CONJUNCAO,
    PREPOSICAO,
    ADVERBIO,
    ARTIGO,
    NUMERAL,
    PRONOME,
    VERBO
};

int estadoAtual;
unordered_map<string, int> tabela;

void cadastrar(int tipo, string palavra);
int buscar(string palavra);
%}

%option noyywrap

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
        cadastrar(estadoAtual, YYText());
    }
    else
    {
        switch(buscar(YYText()))
        {
            case ADJETIVO: cout << YYText() << ": adjetivo" << endl; break;
            case SUBSTANTIVO: cout << YYText() << ": substantivo" << endl; break;
            case INTERJEICAO: cout << YYText() << ": interjeição" << endl; break;
            case CONJUNCAO: cout << YYText() << ": conjunção" << endl; break;
            case PREPOSICAO: cout << YYText() << ": preposição" << endl; break;
            case ADVERBIO: cout << YYText() << ": advérbio" << endl; break;
            case ARTIGO: cout << YYText() << ": artigo" << endl; break;
            case NUMERAL: cout << YYText() << ": numeral" << endl; break;
            case PRONOME: cout << YYText() << ": pronome" << endl; break;
            case VERBO: cout << YYText() << ": verbo" << endl; break;
            default: cout << YYText() << ": não reconhecido" << endl; break;
        }
    }
}

.           ;

%%

int main()
{
    yyFlexLexer lexer;
    lexer.yylex();
    return 0;
}

void cadastrar(int tipo, string palavra)
{
    if(buscar(palavra) != CONSULTA)
    {
        cout << "Palavra já cadastrada: " << palavra << endl;
    }
    else
    {
        tabela.insert({palavra, tipo});
        // cout << "Palavra cadastrada: " << palavra << endl;
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