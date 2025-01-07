/* Léxico para reconhecer a ast gerada */
%option noyywrap
%{
#include <iostream>
#include <string>
#include "tokens.h"
#include "types.h"

using std::cout;
using std::string;

extern Token *token;
extern bool erroLexico;
extern bool erroSintatico;

// Marcadores internos para o léxico
int numColuna = 1;
int numLinha = 1;

// Tipos de erros
enum {TOKEN_DESCONHECIDO};

// Protótipos de funções
void atualizaColuna();
int emitirErroLexico(int erro);
void copiarToken(int tipo, bool copiarTexto);
%}

/* Declarações regulares */
/* Gerais */
letra       [A-Za-z]
decimal     [0-9]
espaco      [ ]
nova_linha  \n
tab         \t

/* Definições */
id          ({letra}|_)+({letra}|{decimal}|_)*
num_int     {decimal}+
string      ["](\\.|[^\"])*["]
caracter    [']([^\n\'\\]|\\[abfrtnv\'\"?0\\])[']

%%

AST -->     ;

CONSTANT    copiarToken(CONSTANT, false); return CONSTANT; 
GLOBAL      copiarToken(GLOBAL, false); return GLOBAL;
VARIABLE    copiarToken(VARIABLE, false); return VARIABLE;
PARAMETER   copiarToken(PARAMETER, false); return PARAMETER; 
TYPE        copiarToken(TYPE, false); return TYPE;
VALUE       copiarToken(VALUE, false); return VALUE;

FUNCTION        copiarToken(FUNCTION, false); return FUNCTION;
END_FUNCTION    copiarToken(END_FUNCTION, false); return END_FUNCTION;
RETURN_TYPE     copiarToken(RETURN_TYPE, false); return RETURN_TYPE;

DO_WHILE        copiarToken(DO_WHILE, false); return DO_WHILE;
IF              copiarToken(IF, false); return IF;
WHILE           copiarToken(WHILE, false); return WHILE;
FOR             copiarToken(FOR, false); return FOR;
PRINTF          copiarToken(PRINTF, false); return PRINTF;
SCANF           copiarToken(SCANF, false); return SCANF;
EXIT            copiarToken(EXIT, false); return EXIT;
RETURN          copiarToken(RETURN, false); return RETURN;

void            copiarToken(VOID, false); return VOID; 
int             copiarToken(INT, false); return INT;
char            copiarToken(CHAR, false); return CHAR;

"+"             copiarToken(PLUS, false); return PLUS;
"-"             copiarToken(MINUS, false); return MINUS;
"*"             copiarToken(MULTIPLY, false); return MULTIPLY;
"/"             copiarToken(DIV, false); return DIV;
"%"             copiarToken(REMAINDER, false); return REMAINDER;

"&"             copiarToken(BITWISE_AND, false); return BITWISE_AND;
"|"             copiarToken(BITWISE_OR, false); return BITWISE_OR;
"^"             copiarToken(BITWISE_XOR, false); return BITWISE_XOR;

"&&"            copiarToken(LOGICAL_AND, false); return LOGICAL_AND;
"||"            copiarToken(LOGICAL_OR, false); return LOGICAL_OR;
"=="            copiarToken(EQUAL, false); return EQUAL;
"!="            copiarToken(NOT_EQUAL, false); return NOT_EQUAL;
"<"             copiarToken(LESS_THAN, false); return LESS_THAN;
">"             copiarToken(GREATER_THAN, false); return GREATER_THAN;
"<="            copiarToken(LESS_EQUAL, false); return LESS_EQUAL;
">="            copiarToken(GREATER_EQUAL, false); return GREATER_EQUAL;

">>"            copiarToken(R_SHIFT, false); return R_SHIFT;
"<<"            copiarToken(L_SHIFT, false); return L_SHIFT;

"="             copiarToken(ASSIGN, false); return ASSIGN;
"+="            copiarToken(ADD_ASSIGN, false); return ADD_ASSIGN;
"-="            copiarToken(MINUS_ASSIGN, false); return MINUS_ASSIGN;

"++"            copiarToken(INC, false); return INC;
"--"            copiarToken(DEC, false); return DEC;
"~"             copiarToken(BITWISE_NOT, false); return BITWISE_NOT;
"!"             copiarToken(NOT, false); return NOT;

"?"             copiarToken(TERNARY_OPER, false); return TERNARY_OPER;

"("             copiarToken(PRT_ESQ, false); return PRT_ESQ;
")"             copiarToken(PRT_DIR, false); return PRT_DIR;
":"             copiarToken(DOIS_PONTOS, false); return DOIS_PONTOS;
"["             copiarToken(CLCT_ESQ, false); return CLCT_ESQ;
"]"             copiarToken(CLCT_DIR, false); return CLCT_DIR;
";"             copiarToken(PNT_VIRG, false); return PNT_VIRG;
","             copiarToken(VIRGULA, false); return VIRGULA;

{id}            copiarToken(IDENTIFIER, true); return IDENTIFIER;
{caracter}      copiarToken(CHARACTER, true); return CHARACTER;
{string}        copiarToken(STRING, true); return STRING;

{num_int}       copiarToken(NUM_INT, false); return NUM_INT; 

{espaco}        atualizaColuna();
{tab}           atualizaColuna();
{nova_linha}    numColuna = 1; numLinha++;

<<EOF>>         return EoF;

.               return emitirErroLexico(TOKEN_DESCONHECIDO);

%%

void atualizaColuna() {
    numColuna += yyleng;
}

void copiarToken(int tipo, bool copiarTexto) {
    atualizaColuna();

    token->tipo = tipo;
    token->linha = numLinha;
    token->coluna = numColuna;

    if(token){
        free(token->valorTexto);
    }

    if(copiarTexto){
        token->valorTexto = strdup(yytext);
        yylval.text = strdup(yytext);
    }else{
        token->valorTexto = NULL;
    }

    if(tipo == NUM_INT){
        token->valorNumero = atoi(yytext);
        yylval.numInt = atoi(yytext);
    }
}

int emitirErroLexico(int erro)
{
    atualizaColuna();

    if(!erroLexico && !erroSintatico){
        switch(erro)
        {
            case TOKEN_DESCONHECIDO:
                cout << "\nerror:lexical:" << numLinha << ":" << numColuna << ": " << yytext << "\n";
            break;

            default:
                break;
        }
    }
    
    erroLexico = true;

    return ERRO;
}