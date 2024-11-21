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

int separarComandos();
int emitirErroSintatico(int erro);
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

%token PNT_VIRG DOIS_PONTOS VIRGULA PRT_ESQ PRT_DIR CLCT_ESQ CLCT_DIR
%token ATRIBUICAO IGUAL

%token NOVA_LINHA ERRO

%token SENO COSSENO TANGENTE ABSOLUTO
%token MAIS MENOS MULTIPLICACAO DIVISAO POTENCIA RESTO 

%token <text> IDENTIFIER CONSTANTE_E CONSTANTE_PI VARIAVEL_X
%token <numInt> NUM_INT 
%token <numDouble> NUM_REAL

%type <numDouble> expressao exPrioM exPrioMM exPrioMMM valorUnario
%type <numDouble> exprCalcula
%type <numDouble> valor valorExpr 
%type <numDouble> funcao

%start inicial
%%

inicial     : configSemRtn NOVA_LINHA   { /*cout << "config sem retorno\n";*/ return SUCESSO; }
            | config NOVA_LINHA         { /*cout << "config\n";*/ return separarComandos(); }
            | simbolos NOVA_LINHA       { /*cout << "simbolos\n";*/ return separarComandos(); }
            | calcula NOVA_LINHA        { /*cout << "calcula\n";*/ return separarComandos(); }
            | NOVA_LINHA                { return SUCESSO; }
            | QUIT NOVA_LINHA           { return FIM; }
            | error                     { return emitirErroSintatico(TOKEN_INESPERADO); }
            ;

config      : ABOUT PNT_VIRG                        { dcmat->showAbout(); }
            | SHOW SETTINGS PNT_VIRG                { dcmat->showSettings(); }
            ;

configSemRtn: RESET SETTINGS PNT_VIRG               { dcmat->resetSettings(); }
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
            | MATRIX IGUAL matriz PNT_VIRG          { dcmat->addMatrix(); }
            ;

limites     : valor DOIS_PONTOS valor   { limites->low = $1; limites->high = $3; }
            ;

valor       : NUM_INT       { $$ = $1; }
            | NUM_REAL      { $$ = $1; }
            ;

simbolos    : IDENTIFIER ATRIBUICAO expressao PNT_VIRG      { dcmat->addSymbol($1, Tipo::FLOAT, $3); }
            | IDENTIFIER ATRIBUICAO matriz
            | SHOW MATRIX PNT_VIRG                          { dcmat->showMatrix(); }
            | SHOW SYMBOLS PNT_VIRG                         { dcmat->showAllSymbols(); }
            ;

// Matriz com apenas um elemento
matriz      : CLCT_ESQ linhas CLCT_DIR
            ;

// Adiciona uma linha
linhas      : linha                         { dcmat->addRowMatrix(); }
            | linhas VIRGULA linha          { dcmat->addRowMatrix(); }
            ;

// Valores de uma linha
linha       : CLCT_ESQ valores CLCT_DIR
            ;

// Adiciona uma coluna
valores     : valor                         { dcmat->addColumnMatrix($1); }
            | valores VIRGULA valor         { dcmat->addColumnMatrix($3); }
            ;

funcao      : SENO PRT_ESQ expressao PRT_DIR        { $$ = std::sin($3); }
            | COSSENO PRT_ESQ expressao PRT_DIR     { $$ = std::cos($3); }
            | TANGENTE PRT_ESQ expressao PRT_DIR    { $$ = std::tan($3); }
            | ABSOLUTO PRT_ESQ expressao PRT_DIR    { $$ = std::abs($3); }
            ;

calcula     : INTEGRATE PRT_ESQ limites VIRGULA funcao PRT_DIR PNT_VIRG
            | SUM PRT_ESQ VIRGULA limites VIRGULA expressao PRT_DIR PNT_VIRG
            | SOLVE DETERMINANT PNT_VIRG
            | SOLVE LINEAR_SYS PNT_VIRG   
            | IDENTIFIER PNT_VIRG                         { dcmat->showSymbol($1); free($1); } 
            | PLOT PNT_VIRG
            | PLOT PRT_ESQ funcao PRT_DIR PNT_VIRG
            | RPN PRT_ESQ expressao PRT_DIR PNT_VIRG
            | expressao                                   { dcmat->showValue($1); }
            ;

// Arrumar
exprCalcula : expressao         { $$ = $1; }
            | VARIAVEL_X        { dcmat->showError(Erro::VariableX); }
            ;

// Em ordem de precedência (da menor prioridade para a maior)
expressao   : PRT_ESQ expressao PRT_DIR         { $$ = $2; }
            | exPrioM                           { $$ = $1; }
            ;
        
exPrioM     : exPrioM MAIS exPrioMM             { $$ = $1 + $3; }
            | exPrioM MENOS exPrioMM            { $$ = $1 - $3; }
            | exPrioMM                          { $$ = $1; }
            ;                               

exPrioMM    : exPrioMM MULTIPLICACAO exPrioMMM  { $$ = $1 * $3; }
            | exPrioMM RESTO exPrioMMM          { $$ = std::fmod($1, $3); }
            | exPrioMM DIVISAO exPrioMMM           
            { 
                if ($3 == 0){
                    dcmat->showError(Erro::DividedByZero);
                    return separarComandos();
                }else{
                    $$ = $1 / $3;
                }
            }
            | exPrioMMM                         { $$ = $1; }
            ;

exPrioMMM   : valorUnario POTENCIA exPrioMMM    { $$ = std::pow($1, $3); }
            | valorUnario                       { $$ = $1; }
            ;

valorUnario : valorExpr         { $$ = $1; }
            | MAIS valorExpr    { $$ = $2; }
            | MENOS valorExpr   { $$ = -$2; }
            ;

valorExpr   : NUM_INT       { $$ = $1; }
            | NUM_REAL      { $$ = $1; }
            | CONSTANTE_E   { $$ = NUM_EULER; }
            | CONSTANTE_PI  { $$ = PI; }
            | IDENTIFIER    { $$ = dcmat->getSymbol($1); free($1); }
            | funcao        { $$ = $1; }
            ;

%%

int separarComandos()
{
    cout << "\n\n";
    return SUCESSO;
}

int emitirErroSintatico(int erro)
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

    return SUCESSO;
}

int yyerror(const void *string)
{
    emitirErroSintatico(TOKEN_FALTANTE);
    cout << "erro sintatico" << endl;
    return FIM;
}