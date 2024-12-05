%{
#include <iostream>
#include <cmath>
#include <string.h>
#include "types.h"
#include "dcmat.h"
#include "ast.h"

using std::cout;
using std::endl;

extern int yytext;

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
// Tipos de retornos
enum { FIM = 0, SUCESSO};

int yylex(void);
int yyparser(void);
void yyerror(const void *string);

int separarComandos();
int emitirErroSintatico(int erro);
%}

%union {
    double numDouble;
    int numInt;
    char *text;
    struct nodeArvore *node;
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

%type <numInt> inteiro
%type <numDouble> numero 
%type <node> expressao exPrioM exPrioMM exPrioMMM
%type <node> funcao valorUnario numericos valorExpr

%start inicial
%%

inicial     : configSemRtn NOVA_LINHA   { /*cout << "config sem retorno\n";*/ return SUCESSO; }
            | config NOVA_LINHA         { /*cout << "config\n";*/ return separarComandos(); }
            | simbSemRtn NOVA_LINHA     { /*cout << "simbolos sem retorno\n";*/ return SUCESSO; }
            | simbolos NOVA_LINHA       { /*cout << "simbolos\n";*/ return separarComandos(); }
            | calcula NOVA_LINHA        { /*cout << "calcula\n";*/ return separarComandos(); }
            | NOVA_LINHA                { return SUCESSO; }
            | QUIT NOVA_LINHA           { return FIM; }
            | error                     { /*cout << "ERRROOOOO\n";*/ return FIM; }
            | ERRO error                { /*cout << "?\n";*/ return FIM; }
            | ERRO                      { /*cout << "ERRO do Lexico\n";*/ return SUCESSO; }
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
            | SET FLOAT PRECISION inteiro PNT_VIRG  { dcmat->setFloatPrecision($4); }
            | SET INTEGRAL_STEPS inteiro PNT_VIRG   { dcmat->setIntegralSteps($3); }
            | SET H_VIEW limites PNT_VIRG           { dcmat->setHView(limites->low, limites->high); }
            | SET V_VIEW limites PNT_VIRG           { dcmat->setVView(limites->low, limites->high); }
            | MATRIX IGUAL matriz PNT_VIRG          { dcmat->addMatrix(); }
            ;

limites     : numero DOIS_PONTOS numero   { limites->low = $1; limites->high = $3; }
            ;

inteiro     : NUM_INT           { $$ = $1; }
            | MAIS NUM_INT      { $$ = $2; }
            | MENOS NUM_INT     { $$ = -$2; }
            ;

numero      : inteiro           { $$ = $1; }
            | NUM_REAL          { $$ = $1; }
            | MAIS NUM_REAL     { $$ = $2; }
            | MENOS NUM_REAL    { $$ = -$2; }
            ;

// Matriz com apenas um elemento
matriz      : CLCT_ESQ linhas CLCT_DIR
            ;

// Adiciona uma linha
linhas      : linha                        
            | linhas VIRGULA linha          
            ;

// Valores de uma linha
linha       : CLCT_ESQ valores CLCT_DIR     { dcmat->addRowMatrix(); }
            ;

// Adiciona uma coluna
valores     : numero                         { dcmat->addColumnMatrix($1); }
            | valores VIRGULA numero         { dcmat->addColumnMatrix($3); }
            ;

simbSemRtn  : IDENTIFIER ATRIBUICAO matriz PNT_VIRG     { dcmat->addSymbol($1, Tipo::MATRIX, 0); free($1); }
            | SHOW SYMBOLS PNT_VIRG                     { dcmat->showAllSymbols(); }
            ;

simbolos    : IDENTIFIER ATRIBUICAO expressao PNT_VIRG      { dcmat->addFloatSymbol($1, $3); free($1); }
            | SHOW MATRIX PNT_VIRG                          { dcmat->showMatrix(nullptr); }
            ;

calcula     : SUM PRT_ESQ IDENTIFIER VIRGULA limites VIRGULA expressao PRT_DIR PNT_VIRG     { dcmat->calculateSum($7, limites, false, $3); free($3); }
            | SUM PRT_ESQ VARIAVEL_X VIRGULA limites VIRGULA expressao PRT_DIR PNT_VIRG     { dcmat->calculateSum($7, limites, true, ""); }
            | INTEGRATE PRT_ESQ limites VIRGULA expressao PRT_DIR PNT_VIRG                  { dcmat->calculateIntegral(limites, $5); }
            | SOLVE DETERMINANT PNT_VIRG                    { dcmat->solveDeterminant(); }
            | SOLVE LINEAR_SYS PNT_VIRG                     { dcmat->solveLinearSystem(); }
            | IDENTIFIER PNT_VIRG                           { dcmat->showSymbol($1); free($1); } 
            | RPN PRT_ESQ expressao PRT_DIR PNT_VIRG        { dcmat->showRpnExpression($3); }
            | expressao                                     { dcmat->showExpression($1); }                      
            | PLOT PRT_ESQ funcao PRT_DIR PNT_VIRG
            | PLOT PNT_VIRG
            ;

// Em ordem de precedência (da menor prioridade para a maior)
expressao   : exPrioM                           { $$ = $1; }
            ;

exPrioM     : exPrioM MAIS exPrioMM             { $$ = makeOperatorNode(Operador::ADICAO, $1, $3); }
            | exPrioM MENOS exPrioMM            { $$ = makeOperatorNode(Operador::SUBTRACAO, $1, $3); }
            | exPrioMM                          { $$ = $1; }
            ;                               

exPrioMM    : exPrioMM MULTIPLICACAO exPrioMMM  { $$ = makeOperatorNode(Operador::MULTIPLICACAO, $1, $3); }
            | exPrioMM RESTO exPrioMMM          { $$ = makeOperatorNode(Operador::RESTO, $1, $3); }
            | exPrioMM DIVISAO exPrioMMM        { $$ = makeOperatorNode(Operador::DIVISAO, $1, $3); }
            | exPrioMMM                         { $$ = $1; }
            ;

exPrioMMM   : valorUnario POTENCIA exPrioMMM    { $$ = makeOperatorNode(Operador::POTENCIA, $1, $3); }
            | PRT_ESQ expressao PRT_DIR         { $$ = $2; }
            | valorUnario                       { $$ = $1; }
            ;

valorUnario : valorExpr         { $$ = $1; }
            | MAIS valorExpr    { $$ = makeUnaryNode(Operador::POSITIVO, $2); }
            | MENOS valorExpr   { $$ = makeUnaryNode(Operador::NEGATIVO, $2); }
            | numericos         { $$ = $1; }
            | MAIS numericos    { $$ = makeUnaryNode(Operador::POSITIVO, $2); }
            | MENOS numericos   { $$ = makeUnaryNode(Operador::NEGATIVO, $2); }
            ;

numericos   : numero        { $$ = makeConstantNode($1); }
            | CONSTANTE_E   { $$ = makeConstantNode(NUM_EULER); }
            | CONSTANTE_PI  { $$ = makeConstantNode(PI); }
            ;

valorExpr   : VARIAVEL_X    { $$ = makeXNode(token); }
            | funcao        { $$ = $1; }
            | IDENTIFIER    { $$ = makeIdNode($1); free($1); }
            ;

funcao      : SENO PRT_ESQ expressao PRT_DIR        { $$ = makeFunctionNode(Funcao::SENO, $3); }
            | COSSENO PRT_ESQ expressao PRT_DIR     { $$ = makeFunctionNode(Funcao::COSSENO, $3); }
            | TANGENTE PRT_ESQ expressao PRT_DIR    { $$ = makeFunctionNode(Funcao::TANGENTE, $3); }
            | ABSOLUTO PRT_ESQ expressao PRT_DIR    { $$ = makeFunctionNode(Funcao::ABSOLUTO, $3); }
            ;

%%

int separarComandos()
{
    cout << "\n\n";
    return SUCESSO;
}

int emitirErroSintatico(int erro)
{
    cout << "\nSYNTAX ERROR: ";

    switch(erro)
    {
        case TOKEN_FALTANTE:
            cout << "Incomplete Command\n";
            break;

        case TOKEN_INESPERADO:
            if(strcmp(token, "\n") == 0){
                cout << "[\\n]\n";
            }else{
                cout << "[" << token << "]\n";
            }
            break;

        default:
            break;
    }

    return SUCESSO;
}

void yyerror(const void *string)
{
    emitirErroSintatico(TOKEN_INESPERADO);
    cout << "erro sintatico" << endl;
}