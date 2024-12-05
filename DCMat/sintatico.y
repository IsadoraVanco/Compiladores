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
extern struct nodeArvore *nodeLeitura;
extern bool erroLexico;
extern bool erroSintatico;

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

inicial     : configSemRtn              { /*cout << "config sem retorno\n";*/ return SUCESSO; }
            | config                    { /*cout << "config\n";*/ return separarComandos(); }
            | simbSemRtn                { /*cout << "simbolos sem retorno\n";*/ return SUCESSO; }
            | simbolos                  { /*cout << "simbolos\n";*/ return separarComandos(); }
            | calcula                   { /*cout << "calcula\n";*/ return separarComandos(); }
            | NOVA_LINHA                { return SUCESSO; }
            | QUIT NOVA_LINHA           { return FIM; }
            | erros                     { erroSintatico = false; erroLexico = false; return SUCESSO; }
            ;

erros       : ERRO                      { /*cout << "\nlex ";*/ }                
            | ERRO erros                { /*cout << "\nlex+ ";*/ }
            | ERRO NOVA_LINHA           { /*cout << "\nlex nl ";*/ }
            | error erros               { /*cout << "\nerro+ ";*/}
            | error NOVA_LINHA          { /*cout << "\nerro nl";*/ emitirErroSintatico(TOKEN_FALTANTE); }
            | error                     { /*cout << "\nQUAL ERRO";*/ emitirErroSintatico(TOKEN_INESPERADO); }
            ;

config      : ABOUT PNT_VIRG NOVA_LINHA             { dcmat->showAbout(); }
            | SHOW SETTINGS PNT_VIRG NOVA_LINHA     { dcmat->showSettings(); }
            ;

configSemRtn: RESET SETTINGS PNT_VIRG NOVA_LINHA        { dcmat->resetSettings(); }
            | SET AXIS ON PNT_VIRG NOVA_LINHA           { dcmat->setDrawAxis(true); }
            | SET AXIS OFF PNT_VIRG NOVA_LINHA          { dcmat->setDrawAxis(false); }
            | SET ERASE PLOT ON PNT_VIRG NOVA_LINHA     { dcmat->setErasePlot(true); }
            | SET ERASE PLOT OFF PNT_VIRG NOVA_LINHA    { dcmat->setErasePlot(false); }
            | SET DOTS ON PNT_VIRG NOVA_LINHA           { dcmat->setConnectDots(true); }
            | SET DOTS OFF PNT_VIRG NOVA_LINHA          { dcmat->setConnectDots(false); }
            | SET FLOAT PRECISION inteiro PNT_VIRG NOVA_LINHA   { dcmat->setFloatPrecision($4); }
            | SET INTEGRAL_STEPS inteiro PNT_VIRG NOVA_LINHA    { dcmat->setIntegralSteps($3); }
            | SET H_VIEW limites PNT_VIRG NOVA_LINHA            { dcmat->setHView(limites->low, limites->high); }
            | SET V_VIEW limites PNT_VIRG NOVA_LINHA            { dcmat->setVView(limites->low, limites->high); }
            | MATRIX IGUAL matriz PNT_VIRG NOVA_LINHA           { dcmat->addMatrix(); }
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

simbSemRtn  : IDENTIFIER ATRIBUICAO matriz PNT_VIRG NOVA_LINHA  { dcmat->addSymbol($1, Tipo::MATRIX, 0); free($1); }
            | SHOW SYMBOLS PNT_VIRG NOVA_LINHA                  { dcmat->showAllSymbols(); }
            ;

simbolos    : IDENTIFIER ATRIBUICAO expressao PNT_VIRG NOVA_LINHA   { dcmat->addFloatSymbol($1, $3); free($1); }
            | SHOW MATRIX PNT_VIRG NOVA_LINHA                       { dcmat->showMatrix(nullptr); }
            ;

calcula     : SUM PRT_ESQ IDENTIFIER VIRGULA limites VIRGULA expressao PRT_DIR PNT_VIRG NOVA_LINHA  { dcmat->calculateSum($7, limites, false, $3); free($3); }
            | SUM PRT_ESQ VARIAVEL_X VIRGULA limites VIRGULA expressao PRT_DIR PNT_VIRG NOVA_LINHA  { dcmat->calculateSum($7, limites, true, ""); }
            | INTEGRATE PRT_ESQ limites VIRGULA expressao PRT_DIR PNT_VIRG NOVA_LINHA               { dcmat->calculateIntegral(limites, $5); }
            | PLOT PRT_ESQ expressao PRT_DIR PNT_VIRG NOVA_LINHA    { dcmat->plotFunction($3); }
            | RPN PRT_ESQ expressao PRT_DIR PNT_VIRG NOVA_LINHA     { dcmat->showRpnExpression($3); }
            | SOLVE DETERMINANT PNT_VIRG NOVA_LINHA                 { dcmat->solveDeterminant(); }
            | SOLVE LINEAR_SYS PNT_VIRG NOVA_LINHA                  { dcmat->solveLinearSystem(); }
            | IDENTIFIER PNT_VIRG NOVA_LINHA                        { dcmat->showSymbol($1); free($1); } 
            | PLOT PNT_VIRG NOVA_LINHA                              { dcmat->plotFunction(nullptr); }
            | expressao NOVA_LINHA                                  { dcmat->showExpression($1); }                      
            ;

// Em ordem de precedência (da menor prioridade para a maior)
expressao   : exPrioM                           { $$ = $1; nodeLeitura = $$; }
            ;

exPrioM     : exPrioM MAIS exPrioMM             { $$ = makeOperatorNode(Operador::ADICAO, $1, $3); nodeLeitura = $$; }
            | exPrioM MENOS exPrioMM            { $$ = makeOperatorNode(Operador::SUBTRACAO, $1, $3); nodeLeitura = $$; }
            | exPrioMM                          { $$ = $1; nodeLeitura = $$; }
            ;                               

exPrioMM    : exPrioMM MULTIPLICACAO exPrioMMM  { $$ = makeOperatorNode(Operador::MULTIPLICACAO, $1, $3); nodeLeitura = $$; }
            | exPrioMM RESTO exPrioMMM          { $$ = makeOperatorNode(Operador::RESTO, $1, $3); nodeLeitura = $$; }
            | exPrioMM DIVISAO exPrioMMM        { $$ = makeOperatorNode(Operador::DIVISAO, $1, $3); nodeLeitura = $$; }
            | exPrioMMM                         { $$ = $1; nodeLeitura = $$; }
            ;

exPrioMMM   : valorUnario POTENCIA exPrioMMM    { $$ = makeOperatorNode(Operador::POTENCIA, $1, $3); nodeLeitura = $$; }
            | PRT_ESQ expressao PRT_DIR         { $$ = $2; nodeLeitura = $$; }
            | valorUnario                       { $$ = $1; nodeLeitura = $$; }
            ;

valorUnario : valorExpr         { $$ = $1; }
            | MAIS valorExpr    { $$ = makeUnaryNode(Operador::POSITIVO, $2); nodeLeitura = $$; }
            | MENOS valorExpr   { $$ = makeUnaryNode(Operador::NEGATIVO, $2); nodeLeitura = $$; }
            | numericos         { $$ = $1; nodeLeitura = $$; }
            | MAIS numericos    { $$ = makeUnaryNode(Operador::POSITIVO, $2); nodeLeitura = $$; }
            | MENOS numericos   { $$ = makeUnaryNode(Operador::NEGATIVO, $2); nodeLeitura = $$; }
            ;

numericos   : numero        { $$ = makeConstantNode($1); nodeLeitura = $$; }
            | CONSTANTE_E   { $$ = makeConstantNode(NUM_EULER); nodeLeitura = $$; }
            | CONSTANTE_PI  { $$ = makeConstantNode(PI); nodeLeitura = $$; }
            ;

valorExpr   : VARIAVEL_X    { $$ = makeXNode(token); nodeLeitura = $$; }
            | funcao        { $$ = $1; nodeLeitura = $$; }
            | IDENTIFIER    { $$ = makeIdNode($1); free($1); nodeLeitura = $$; }
            ;

funcao      : SENO PRT_ESQ expressao PRT_DIR        { $$ = makeFunctionNode(Funcao::SENO, $3); nodeLeitura = $$; }
            | COSSENO PRT_ESQ expressao PRT_DIR     { $$ = makeFunctionNode(Funcao::COSSENO, $3); nodeLeitura = $$; }
            | TANGENTE PRT_ESQ expressao PRT_DIR    { $$ = makeFunctionNode(Funcao::TANGENTE, $3); nodeLeitura = $$; }
            | ABSOLUTO PRT_ESQ expressao PRT_DIR    { $$ = makeFunctionNode(Funcao::ABSOLUTO, $3); nodeLeitura = $$; }
            ;

%%

int separarComandos()
{
    cout << "\n\n";
    return SUCESSO;
}

int emitirErroSintatico(int erro)
{
    if(!erroSintatico && !erroLexico){
        cout << "\nSYNTAX ERROR: ";

        switch(erro)
        {
            case TOKEN_FALTANTE:
                cout << "Incomplete Command\n\n";
                break;

            case TOKEN_INESPERADO:
                if(strcmp(token, "\n") == 0){
                    cout << "[\\n]\n";
                }else{
                    cout << "[" << token << "]\n\n";
                }
                break;

            default:
                break;
        }
    }

    erroSintatico = true;

    return SUCESSO;
}

void yyerror(const void *string)
{
    // cout << "\nerro sintatico";

    if(*token == '\n'){
        emitirErroSintatico(TOKEN_FALTANTE);
    }else{
        emitirErroSintatico(TOKEN_INESPERADO);
    }
}