%{
#include <iostream>

using std::cout;
using std::endl;

extern int yytext;
extern bool erroLexico;
extern bool erroSintatico;

void yyerror(void *s);

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
// Tipos de retornos
enum { FIM = 0, SUCESSO};

int yylex(void);
int yyparser(void);
void yyerror(const void *string);

int emitirErroSintatico(int erro);

%}

%union {
    int numInt;
    char *text;
}

%defines "tokens.h"

%token CONSTANT GLOBAL VARIABLE PARAMETER
%token VALUE TYPE
%token FUNCTION END_FUNCTION RETURN_TYPE
%token DO_WHILE IF WHILE FOR PRINTF SCANF EXIT RETURN
%token VOID INT CHAR

%token PLUS MINUS MULTIPLY DIV REMAINDER
%token BITWISE_AND BITWISE_OR BITWISE_XOR
%token LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL
%token LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token R_SHIFT L_SHIFT
%token ASSIGN ADD_ASSIGN MINUS_ASSIGN
%token INC DEC BITWISE_NOT NOT
%token TERNARY_OPER

%token PRT_ESQ PRT_DIR DOIS_PONTOS
%token CLCT_ESQ CLCT_DIR PNT_VIRG VIRGULA
%token EoF

%token <text> STRING IDENTIFIER CHARACTER
%token <numInt> NUM_INT

%type <numInt> valorNumero

%start inicial
%%

inicial     : def EoF           { return SUCESSO; }
            ;

def         : defConst def
            | defGlobal def
            | defFuncao def 
            | // Vazia
            ;

// Definição de variáveis locais
defConst    : CONSTANT DOIS_PONTOS IDENTIFIER VALUE DOIS_PONTOS valorNumero
            ;

valorNumero : PLUS NUM_INT  { $$ = $2; }
            | MINUS NUM_INT { $$ = -$2; }
            | NUM_INT       { $$ = $1; }
            ; 

// Definição de variável global
defGlobal   : GLOBAL VARIABLE DOIS_PONTOS IDENTIFIER TYPE DOIS_PONTOS tipoVar
            ;

tipoVar     : tipo
            | tipo vetor
            | ponteiro 
            | ponteiro vetor 
            ;

tipo        : INT      
            | CHAR     
            ;

ponteiro    : tipo MULTIPLY qtdPnt
            | VOID MULTIPLY qtdPnt
            ;

qtdPnt      : MULTIPLY qtdPnt
            | // Vazia
            ;

vetor       : CLCT_ESQ NUM_INT CLCT_DIR vetor
            | // Vazia
            ;

// Definição da função
defFuncao   : FUNCTION DOIS_PONTOS IDENTIFIER retornoFunc paramFunc defLocais listaCmd END_FUNCTION
            ;

retornoFunc : RETURN_TYPE DOIS_PONTOS tipo
            | RETURN_TYPE DOIS_PONTOS ponteiro
            | RETURN_TYPE DOIS_PONTOS VOID
            ;

paramFunc   : PARAMETER DOIS_PONTOS IDENTIFIER TYPE DOIS_PONTOS tipoVar paramFunc
            | //Vazia
            ;

listaCmd    : comando maisCmd
            | // Vazia
            ;

maisCmd     : PNT_VIRG comando
            | // Vazia
            ;

comando     : DO_WHILE PRT_ESQ listaCmd VIRGULA expr PRT_DIR
            | IF PRT_ESQ expr VIRGULA listaCmd cmdElse PRT_DIR
            | WHILE PRT_ESQ expr VIRGULA listaCmd PRT_DIR
            | FOR PRT_ESQ cmdFor VIRGULA cmdFor VIRGULA cmdFor VIRGULA listaCmd PRT_DIR
            | PRINTF PRT_ESQ STRING auxPrint PRT_DIR
            | SCANF PRT_ESQ STRING VIRGULA endScan PRT_DIR
            | EXIT PRT_ESQ expr PRT_DIR
            | RETURN PRT_ESQ exprReturn PRT_DIR
            | expr
            ;

cmdElse     : VIRGULA listaCmd
            | // Vazia
            ;

cmdFor      : expr
            | // Vazia
            ;

auxPrint    : VIRGULA expr auxPrint
            | //Vazia
            ;

endScan     : BITWISE_AND PRT_ESQ IDENTIFIER PRT_DIR 
            ;

exprReturn  : expr
            | // Vazia
            ;

// Definição de variáveis locais
defLocais   : VARIABLE DOIS_PONTOS IDENTIFIER TYPE DOIS_PONTOS tipoVar defLocais
            | // Vazia
            ; 

// Definição de expressões
expr        : exprBin
            | exprUn
            | exprTern
            | exprPrim
            ;

exprBin     : operBinUn PRT_ESQ expr VIRGULA expr PRT_DIR 
            | operBin PRT_ESQ expr VIRGULA expr PRT_DIR 
            ;

operBinUn   : PLUS      
            | MINUS    
            | MULTIPLY
            ;

operBin     : DIV     
            | REMAINDER     
            | BITWISE_AND  
            | BITWISE_OR   
            | BITWISE_XOR  
            | LOGICAL_AND  
            | LOGICAL_OR   
            | EQUAL        
            | NOT_EQUAL    
            | LESS_THAN    
            | GREATER_THAN 
            | LESS_EQUAL   
            | GREATER_EQUAL
            | R_SHIFT      
            | L_SHIFT      
            | ASSIGN       
            | ADD_ASSIGN   
            | MINUS_ASSIGN 
            ;

exprUn      : operBinUn PRT_ESQ expr PRT_DIR 
            | operUn PRT_ESQ expr PRT_DIR 
            | PRT_ESQ expr PRT_DIR INC 
            | PRT_ESQ expr PRT_DIR DEC
            ;

operUn      : INC          
            | DEC          
            | BITWISE_NOT  
            | NOT          
            ;

exprTern    : TERNARY_OPER PRT_ESQ expr VIRGULA expr VIRGULA expr PRT_DIR
            ;

exprPrim    : NUM_INT
            | CHARACTER 
            | STRING 
            | IDENTIFIER
            ;

%%

int emitirErroSintatico(int erro)
{
    if(!erroSintatico && !erroLexico){
        cout << "\nSYNTAX ERROR: ";

        switch(erro)
        {
            case TOKEN_FALTANTE:
                cout << "Incomplete Comand";
                break;

            case TOKEN_INESPERADO:
                cout << "[" << token->valorTexto << "]";
                break;

            default:
                break;
        }

        cout << ":" << token->linha << ":" << token->coluna << "\n";
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