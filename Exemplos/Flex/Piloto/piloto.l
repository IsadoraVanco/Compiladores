%{
// Aqui, declara-se constantes, variáveis e protótipos de funções
// Tudo isso, vai direto para o arquivo lex.yy.cc

#include <stdio.h>

// Maneira mais comum de declarar os tokens
enum {IF, THEN, ELSE, ID, NUM, OPERADOR};
%}

/* Desativa a opção de processar mais de um arquivo */
%option noyywrap

/* Aqui vão declarações de variáveis e definições regulares */

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
echo            ECHO;
{id}            return ID;
{num}           return NUM;
"<"             return OPERADOR;
"<="            return OPERADOR;
">"             return OPERADOR;
">="            return OPERADOR;
"=="            return OPERADOR;
"!="            return OPERADOR;
.               printf("%s\n", yytext);
<<EOF>>         return 0;

%%

int main() {
    yylex();
    return 0;
}