/* Desativa a opção de processar mais de um arquivo */
%option noyywrap
%{
// Um reconhecedor simples utilizando mais classes
// Declara os tokens
#include "tokens.h"
#include <FlexLexer.h>

%}

/* Declarações regulares */
delimitador [ \t\n]
brancos     {delimitador}+
letra       [A-Za-z]
digito      [0-9]
id          {letra}({letra}|{digito})*
num         {digito}+(\.{digito}+)?(E[+-]?{digito}+)?

%%

{brancos}       ; // Nenhuma ação
if              return IF;
then            return THEN;
else            return ELSE;
{id}            return ID;
{num}           return NUMERO;
"<"             return OPERADOR;
"<="            return OPERADOR;
">"             return OPERADOR;
">="            return OPERADOR;
"=="            return OPERADOR;
"!="            return OPERADOR;
.               ECHO; // Ou utilizar ECHO

%%

// Não é necessário funções auxiliares, pois estão todas no outro arquivo