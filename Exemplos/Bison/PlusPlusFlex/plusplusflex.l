%{
#include "plusplusflex.tab.h"
%}

%option yylineno
%option noyywrap

letra       [a-zA-Z]
digito      [0-9]

numero      {digito}+("."{digito}+)?
variavel    [{letra}_]+({digito}|_|{letra})* 

%%

[ \t]+      ;
{numero}    yylval.numero = atof(yytext); return NUMERO;
{variavel}  strcpy(yylval.variavel, yytext); return VARIAVEL;
.|\n        return yytext[0];

%%