%option noyywrap
%{
#include <iostream>
#include <string>
#include "tokens.h"

using std::cout;
using std::string;

extern char *token;

// Tipos de erros
enum {TOKEN_DESCONHECIDO};

// Protótipos de funções
int emitirErroLexico(int erro);
void copiarToken();
%}

/* Declarações regulares */
/* Gerais */
letra       [A-Za-z]
decimal     [0-9]
espaco      [ \t]
nova_linha  \n

/* Definições */
id          {letra}+({letra}|{decimal}|_)*
num_int     {decimal}+
num_real    {decimal}+"."{decimal}+
const_pi    [Pp][Ii]
const_e     [Ee]
var_x       [Xx]

%%

about           copiarToken(); return ABOUT;
axis            copiarToken(); return AXIS;
connect_dots    copiarToken(); return DOTS;
determinant     copiarToken(); return DETERMINANT;
erase           copiarToken(); return ERASE;
float           copiarToken(); return FLOAT;
h_view          copiarToken(); return H_VIEW;
integral_steps  copiarToken(); return INTEGRAL_STEPS;
integrate       copiarToken(); return INTEGRATE;
linear_system   copiarToken(); return LINEAR_SYS;
matrix          copiarToken(); return MATRIX;
off             copiarToken(); return OFF;
on              copiarToken(); return ON;
plot            copiarToken(); return PLOT;
precision       copiarToken(); return PRECISION;
quit            copiarToken(); return QUIT;
reset           copiarToken(); return RESET;
rpn             copiarToken(); return RPN;
set             copiarToken(); return SET;
settings        copiarToken(); return SETTINGS;
show            copiarToken(); return SHOW;
solve           copiarToken(); return SOLVE;
sum             copiarToken(); return SUM;
symbols         copiarToken(); return SYMBOLS;
v_view          copiarToken(); return V_VIEW;

sen             copiarToken(); return SENO;
cos             copiarToken(); return COSSENO;
tan             copiarToken(); return TANGENTE;
abs             copiarToken(); return ABSOLUTO;

"+"             copiarToken(); return MAIS; 
"-"             copiarToken(); return MENOS;
"*"             copiarToken(); return MULTIPLICACAO;
"/"             copiarToken(); return DIVISAO;
"^"             copiarToken(); return POTENCIA;
"%"             copiarToken(); return RESTO;

"("             copiarToken(); return PRT_ESQ;
")"             copiarToken(); return PRT_DIR;

":"             copiarToken(); return DOIS_PONTOS;
"="             copiarToken(); return IGUAL;
":="            copiarToken(); return ATRIBUICAO;
"["             copiarToken(); return CLCT_ESQ;
"]"             copiarToken(); return CLCT_DIR;
";"             copiarToken(); return PNT_VIRG;
","             copiarToken(); return VIRGULA;

{const_pi}      copiarToken(); return CONSTANTE_PI;
{const_e}       copiarToken(); return CONSTANTE_E;
{var_x}         copiarToken(); return VARIAVEL_X;

{nova_linha}    copiarToken(); return NOVA_LINHA;
{espaco}        ;

{num_real}      {
                    yylval.numDouble = atof(yytext); 
                    copiarToken(); 
                    return NUM_REAL;
}

{num_int}       {
                    yylval.numInt = atoi(yytext); 
                    copiarToken(); 
                    return NUM_INT;
}

{id}            { 
                    yylval.text = strdup(yytext); 
                    copiarToken(); 
                    return IDENTIFIER;  
}      

.               emitirErroLexico(TOKEN_DESCONHECIDO); return ERRO; 

%%

void copiarToken()
{
    if(token){
        free(token);
    }
    token = strdup(yytext);
}

int emitirErroLexico(int erro)
{
    switch(erro)
    {
        case TOKEN_DESCONHECIDO:
            cout << "\nInvalid Symbol: " << yytext << "\n\n";
           break;

        default:
            break;
    }

    return ERRO;
}