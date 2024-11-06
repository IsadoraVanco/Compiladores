%option noyywrap
%{
#include <iostream>

extern YYSTYPE yylval;

// Tipos de erros
enum {TOKEN_DESCONHECIDO, ID_GRANDE};

%}

/* Declarações regulares */
/* Gerais */
letra       [A-Za-z]
decimal     [0-9]
espaco      [ ]
nova_linha  \n

/* Definições */
id          {letra}+({letra}|{decimal}|_)*
num_int     (+|-)?{decimal}+
num_real    (+|-)?{decimal}+"."{decimal}+
const_pi    [Pp][Ii]
const_e     [Ee]

%%

about           return ABOUT;
axis            return AXIS;
connect_dots    return DOTS;
determinant     return DETERMINANT;
erase           return ERASE;
float           return FLOAT;
h_view          return H_VIEW;
integral_steps  return INTEGRAL_STEPS;
integrate       return INTEGRATE;
linear_system   return LINEAR_SYS;
matrix          return MATRIX;
off             return OFF;
on              return ON;
plot            return PLOT;
precision       return PRECISION;
quit            return QUIT;
reset           return RESET;
rpn             return RPN;
set             return SET;
settings        return SETTINGS;
show            return SHOW;
solve           return SOLVE;
sum             return SUM;
symbols         return SYMBOLS;
v_view          return V_VIEW;

sen             return SENO;
cos             return COSSENO;
tan             return TANGENTE;
abs             return ABSOLUTO;

x               return VARIAVEL_X;

"+"             return MAIS; 
"-"             return MENOS;
"*"             return MULTIPLICACAO;
"/"             return DIVISAO;
"^"             return POTENCIA;
"%"             return RESTO;

"("             return PARENTESES_ESQ;
")"             return PARENTESES_DIR;

":"             return DOIS_PONTOS;
"="             return IGUAL;
":="            return ATRIBUICAO;
"["             return COLCHETE_ESQ;
"]"             return COLCHETE_DIR;
";"             return PONTO_VIRGULA;
","             return VIRGULA;

{const_pi}      return CONSTANTE_PI;
{const_e}       return CONSTANTE_E;

{nova_linha}    return NOVA_LINHA;

{num_real}      return NUM_REAL;
{num_int}       return NUM_INT;

{id}            return IDENTIFIER;        

.               emitirErroLexico(TOKEN_DESCONHECIDO, numLinhas, numColunas); 

%%
