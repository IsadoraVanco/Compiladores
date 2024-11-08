%{
#include <iostream>
#include "dcmat.h"

using std::cout;
using std::endl;

extern int yytext;

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};

int yylex(void);
int yyparser(void);
void yyerror(const void *string);

void emitirErroSintatico(int erro);
%}

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
%token NUM_REAL NUM_INT IDENTIFIER VARIAVEL_X CONSTANTE_PI CONSTANTE_E

%start inicial
%%

inicial     : config NOVA_LINHA         { return 1; }
            | calcula NOVA_LINHA        { cout << "calcula\n"; }
            | simbolos NOVA_LINHA       { cout << "simbolos\n"; }
            | expressao NOVA_LINHA      { cout << "expressao1\n"; }
            | NOVA_LINHA                { return 1; }
            | QUIT                      { return 0; }
            ;

config      : SHOW SETTINGS PONTO_VIRGULA           { dcmat->showSettings(); }
            | RESET SETTINGS PONTO_VIRGULA          { dcmat->resetSettings(); }
            | SET H_VIEW limites PONTO_VIRGULA
            | SET V_VIEW limites PONTO_VIRGULA
            | SET AXIS ON PONTO_VIRGULA
            | SET AXIS OFF PONTO_VIRGULA
            | PLOT PONTO_VIRGULA
            | PLOT PARENTESES_ESQ funcao PARENTESES_DIR PONTO_VIRGULA
            | SET ERASE PLOT OFF PONTO_VIRGULA
            | SET ERASE PLOT ON PONTO_VIRGULA
            | RPN PARENTESES_ESQ expressao PARENTESES_DIR PONTO_VIRGULA
            | SET INTEGRAL_STEPS NUM_INT PONTO_VIRGULA
            | ABOUT PONTO_VIRGULA
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

valor       : NUM_INT
            | NUM_REAL
            ;

nValores    : VIRGULA COLCHETE_ESQ valor nValor COLCHETE_DIR nValores
            | // Vazio
            ;

limites     : valor DOIS_PONTOS valor
            ;

simbolos    : IDENTIFIER ATRIBUICAO expressao
            | IDENTIFIER ATRIBUICAO matriz
            | IDENTIFIER
            | SHOW SYMBOLS
            | SET FLOAT PRECISION NUM_INT
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

void yyerror(const void *string)
{
    emitirErroSintatico(TOKEN_FALTANTE);
    cout << "erro sintatico" << endl;
}