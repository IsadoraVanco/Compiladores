%{
#include <iostream>
#include <cmath>
#include "types.h"
#include "dcmat.h"

using std::cout;
using std::endl;

extern int yytext;

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
// Tipos de retornos
enum { FIM = 0, SUCESSO};

int yylex(void);
int yyparser(void);
int yyerror(const void *string);

void emitirErroSintatico(int erro);
%}

%union {
    double numDouble;
    int numInt;
    char *text;
}

%defines "tokens.h"

%token QUIT SHOW RESET SET PLOT RPN ABOUT
%token SETTINGS H_VIEW V_VIEW AXIS ERASE INTEGRAL_STEPS FLOAT PRECISION DOTS
%token ON OFF

%token INTEGRATE SUM MATRIX SOLVE DETERMINANT LINEAR_SYS SYMBOLS

%token PNT_VIRG DOIS_PONTOS VIRGULA PRT_ESQ PRT_DIR COLCHETE_ESQ COLCHETE_DIR
%token ATRIBUICAO IGUAL

%token NOVA_LINHA ERRO

%token SENO COSSENO TANGENTE ABSOLUTO
%token MAIS MENOS MULTIPLICACAO DIVISAO POTENCIA RESTO 

%token <text> IDENTIFIER CONSTANTE_E CONSTANTE_PI VARIAVEL_X
%token <numInt> NUM_INT 
%token <numDouble> NUM_REAL

%type <numDouble> valor valorExpr 
%type <numDouble> expressao exprCalcula 
%type <numDouble> funcao

%start inicial
%%

inicial     : config NOVA_LINHA         { cout << "config\n"; return SUCESSO; }
            | simbolos NOVA_LINHA       { cout << "simbolos\n"; return SUCESSO; }
            | calcula NOVA_LINHA        { cout << "calcula\n"; return SUCESSO; }
            | NOVA_LINHA                { return SUCESSO; }
            | QUIT                      { return FIM; }
            ;

config      : ABOUT PNT_VIRG                        { dcmat->showAbout(); }
            | SHOW SETTINGS PNT_VIRG                { dcmat->showSettings(); }
            | RESET SETTINGS PNT_VIRG               { dcmat->resetSettings(); }
            | SET AXIS ON PNT_VIRG                  { dcmat->setDrawAxis(true); }
            | SET AXIS OFF PNT_VIRG                 { dcmat->setDrawAxis(false); }
            | SET ERASE PLOT ON PNT_VIRG            { dcmat->setErasePlot(true); }
            | SET ERASE PLOT OFF PNT_VIRG           { dcmat->setErasePlot(false); }
            | SET DOTS ON PNT_VIRG                  { dcmat->setConnectDots(true); }
            | SET DOTS OFF PNT_VIRG                 { dcmat->setConnectDots(false); }
            | SET FLOAT PRECISION NUM_INT PNT_VIRG  { dcmat->setFloatPrecision($4); }
            | SET INTEGRAL_STEPS NUM_INT PNT_VIRG   { dcmat->setIntegralSteps($3); }
            | SET H_VIEW limites PNT_VIRG           { dcmat->setHView(limites->low, limites->high); }
            | SET V_VIEW limites PNT_VIRG           { dcmat->setVView(limites->low, limites->high); }
            ;

limites     : valor DOIS_PONTOS valor   { limites->low = $1; limites->high = $3; }
            ;

valor       : NUM_INT       { $$ = $1; }
            | NUM_REAL      { $$ = $1; }
            ;

simbolos    : IDENTIFIER ATRIBUICAO expressao PNT_VIRG      { dcmat->addVariable($1, Tipo::FLOAT, $3); }
            | IDENTIFIER ATRIBUICAO matriz
            | SHOW MATRIX PNT_VIRG                          { dcmat->showMatrix(); }
            | SHOW SYMBOLS PNT_VIRG                         { dcmat->showAllSymbols(); }
            ;

matriz      : COLCHETE_ESQ COLCHETE_ESQ valor nValor COLCHETE_DIR nValores COLCHETE_DIR
            ;

nValor      : VIRGULA valor nValor  
            | // Vazio
            ;

nValores    : VIRGULA COLCHETE_ESQ valor nValor COLCHETE_DIR nValores
            | // Vazio
            ;

funcao      : SENO PRT_ESQ expressao PRT_DIR        { $$ = std::sin($3); }
            | COSSENO PRT_ESQ expressao PRT_DIR     { $$ = std::cos($3); }
            | TANGENTE PRT_ESQ expressao PRT_DIR    { $$ = std::tan($3); }
            | ABSOLUTO PRT_ESQ expressao PRT_DIR    { $$ = std::abs($3); }
            ;

// Colocar em ordem de prioridade
expressao   : expressao MAIS expressao              { $$ = $1 + $3; }
            | expressao MENOS expressao             { $$ = $1 - $3; }
            | expressao MULTIPLICACAO expressao     { $$ = $1 * $3; }
            | expressao POTENCIA expressao          { $$ = std::pow($1, $3); }
            | expressao RESTO expressao             { $$ = std::fmod($1, $3); }
            | PRT_ESQ expressao PRT_DIR             { $$ = $2; }   
            | valorExpr                             { $$ = $1; }
            | expressao DIVISAO expressao           
            { 
                if ($3 == 0){
                    dcmat->showDivideError();
                    return 1;
                }else{
                    $$ = $1 / $3;
                }
            }
            ;

valorExpr   : NUM_INT       { $$ = $1; }
            | NUM_REAL      { $$ = $1; }
            | CONSTANTE_E   { $$ = dcmat->getNumE(); }
            | CONSTANTE_PI  { $$ = dcmat->getPi(); }
            | IDENTIFIER    { $$ = dcmat->getVariable($1); free($1); }
            ;

calcula     : INTEGRATE PRT_ESQ limites VIRGULA funcao PRT_DIR PNT_VIRG
            | SUM PRT_ESQ VIRGULA limites VIRGULA expressao PRT_DIR PNT_VIRG
            | MATRIX IGUAL matriz PNT_VIRG
            | SOLVE DETERMINANT PNT_VIRG
            | SOLVE LINEAR_SYS PNT_VIRG   
            | IDENTIFIER PNT_VIRG                           { dcmat->showSymbol($1); free($1); } 
            | PLOT PNT_VIRG
            | PLOT PRT_ESQ funcao PRT_DIR PNT_VIRG
            | RPN PRT_ESQ expressao PRT_DIR PNT_VIRG
            | exprCalcula                                   { dcmat->showValue($1); }
            ;

exprCalcula : expressao         { $$ = $1; }
            | VARIAVEL_X        { dcmat->showVariableXError(); }
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
    return SUCESSO;
}