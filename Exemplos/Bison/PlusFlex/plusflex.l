%{
#include "plusflex.tab.h"
%}

%option noyywrap

numero [0-9]+("."[0-9]+)?

%%

[ \t]+      ;
{numero}    yylval = atof(yytext); return NUMERO;
.|\n        return yytext[0];

%%