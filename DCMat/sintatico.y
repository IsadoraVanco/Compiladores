%{
#include <iostream>

using std::cout;
using std::endl;

extern int yytext;

int yylex(void);
int yyparser(void);
void yyerror(const void *string);

void emitirErroSintatico(int erro);

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
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

inicial     : config PONTO_VIRGULA      
            | calcula PONTO_VIRGULA
            | simbolos PONTO_VIRGULA
            | expressao
            | NOVA_LINHA                { return 1; }
            | QUIT                      { return 0; }
            ;

config      : SHOW SETTINGS 
            | RESET SETTINGS 
            | SET H_VIEW limites 
            | SET V_VIEW limites 
            | SET AXIS ON
            | SET AXIS OFF
            | PLOT 
            | PLOT PARENTESES_ESQ funcao PARENTESES_DIR 
            | SET ERASE PLOT OFF 
            | SET ERASE PLOT ON 
            | RPN PARENTESES_ESQ expressao PARENTESES_DIR
            | SET INTEGRAL_STEPS NUM_INT
            | ABOUT
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