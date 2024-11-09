%{
#include <iostream>
#include "types.h"
#include "dcmat.h"

using std::cout;
using std::endl;

extern int yytext;

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};

int yylex(void);
int yyparser(void);
int yyerror(const void *string);

void emitirErroSintatico(int erro);
%}

%union {
    double numDouble;
    int numInt;
}

%defines "tokens.h"

%token QUIT SHOW RESET SET PLOT RPN ABOUT
%token SETTINGS H_VIEW V_VIEW AXIS ERASE INTEGRAL_STEPS FLOAT PRECISION DOTS
%token ON OFF

%token INTEGRATE SUM MATRIX SOLVE DETERMINANT LINEAR_SYS SYMBOLS

%token PONTO_VIRGULA DOIS_PONTOS VIRGULA PARENTESES_ESQ PARENTESES_DIR COLCHETE_ESQ COLCHETE_DIR
%token ATRIBUICAO IGUAL

%token NOVA_LINHA ERRO

%token SENO COSSENO TANGENTE ABSOLUTO
%token MAIS MENOS MULTIPLICACAO DIVISAO POTENCIA RESTO 
%token IDENTIFIER VARIAVEL_X CONSTANTE_PI CONSTANTE_E

%token <numDouble> NUM_REAL
%token <numInt> NUM_INT 

%type <numDouble> valor

%start inicial
%%

inicial     : config NOVA_LINHA         { return 1; }
            | calcula NOVA_LINHA        { cout << "calcula\n"; return 1; }
            | simbolos NOVA_LINHA       { cout << "simbolos\n"; return 1; }
            | expressao NOVA_LINHA      { cout << "expressao1\n"; return 1; }
            | NOVA_LINHA                { return 1; }
            | QUIT                      { return 0; }
            ;

config      : SHOW SETTINGS PONTO_VIRGULA           { dcmat->showSettings(); }
            | RESET SETTINGS PONTO_VIRGULA          { dcmat->resetSettings(); }
            | SET H_VIEW limites PONTO_VIRGULA      { dcmat->setHView(limites->low, limites->high); }
            | SET V_VIEW limites PONTO_VIRGULA      { dcmat->setVView(limites->low, limites->high); }
            | SET AXIS ON PONTO_VIRGULA             { dcmat->setDrawAxis(true); }
            | SET AXIS OFF PONTO_VIRGULA            { dcmat->setDrawAxis(false); }
            | SET ERASE PLOT ON PONTO_VIRGULA       { dcmat->setErasePlot(true); }
            | SET ERASE PLOT OFF PONTO_VIRGULA      { dcmat->setErasePlot(false); }
            | SET DOTS ON PONTO_VIRGULA             { dcmat->setConnectDots(true); }
            | SET DOTS OFF PONTO_VIRGULA            { dcmat->setConnectDots(false); }
            | ABOUT PONTO_VIRGULA                   { dcmat->showAbout(); }
            | SET FLOAT PRECISION NUM_INT PONTO_VIRGULA { dcmat->setFloatPrecision($4); }
            | SET INTEGRAL_STEPS NUM_INT PONTO_VIRGULA  { dcmat->setIntegralSteps($3); }
            | PLOT PONTO_VIRGULA
            | PLOT PARENTESES_ESQ funcao PARENTESES_DIR PONTO_VIRGULA
            | RPN PARENTESES_ESQ expressao PARENTESES_DIR PONTO_VIRGULA
            ;

limites     : valor DOIS_PONTOS valor   { limites->low = $1; limites->high = $3; }
            ;

valor       : NUM_INT       { $$ = $1; }
            | NUM_REAL      { $$ = $1; }
            ;

funcao      : funcoes PARENTESES_ESQ expressao PARENTESES_DIR
            ;

funcoes     : SENO
            | COSSENO
            | TANGENTE
            | ABSOLUTO
            ;

expressao   : expressao operador expressao
            | PARENTESES_ESQ expressao PARENTESES_DIR
            | valorExpr
            | funcao
            ;

valorExpr   : NUM_INT
            | NUM_REAL
            | VARIAVEL_X
            | CONSTANTE_E
            | CONSTANTE_PI
            | IDENTIFIER
            ;

operador    : MAIS
            | MENOS
            | MULTIPLICACAO
            | DIVISAO
            | POTENCIA
            | RESTO
            ;

calcula     : INTEGRATE PARENTESES_ESQ limites VIRGULA funcao PARENTESES_DIR
            | SUM PARENTESES_ESQ VIRGULA limites VIRGULA expressao PARENTESES_DIR
            | MATRIX IGUAL matriz
            | SHOW MATRIX
            | SOLVE DETERMINANT
            | SOLVE LINEAR_SYS
            ;

matriz      : COLCHETE_ESQ COLCHETE_ESQ valor nValor COLCHETE_DIR nValores COLCHETE_DIR
            ;

nValor      : VIRGULA valor nValor
            | // Vazio
            ;

nValores    : VIRGULA COLCHETE_ESQ valor nValor COLCHETE_DIR nValores
            | // Vazio
            ;

simbolos    : IDENTIFIER ATRIBUICAO expressao
            | IDENTIFIER ATRIBUICAO matriz
            | IDENTIFIER
            | SHOW SYMBOLS
            ;

%%

void emitirErroSintatico(int erro)
{
    cout << "SYNTAX ERROR: ";

    switch(erro)
    {
        case TOKEN_FALTANTE:
            cout << "Incomplete Command\n";
            break;

        case TOKEN_INESPERADO:
            cout << "[" << yytext << "]\n";
            break;

        default:
            break;
    } 
}

int yyerror(const void *string)
{
    emitirErroSintatico(TOKEN_FALTANTE);
    cout << "erro sintatico" << endl;
    return 1;
}