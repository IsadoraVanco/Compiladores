/* Não utilizar a biblioteca do flex*/
%option noyywrap
%{
#include <stdbool.h>

bool primeiroToken = true;

void verificarPrimeiroToken();
%}

decimal [0-9]
letra   [a-z]
sinal   [+-]

%%

{letra}+[{letra}{decimal}]*     verificarPrimeiroToken(); printf("%s", yytext);  

{decimal}+                      verificarPrimeiroToken(); printf("%s", yytext);  

{decimal}+e{sinal}?{decimal}+   verificarPrimeiroToken(); printf("%s", yytext);  

{sinal}                         verificarPrimeiroToken(); printf("%s", yytext);  

\n                              ;

.                               verificarPrimeiroToken(); printf("ERRO");  

%%

void verificarPrimeiroToken()
{
    if(!primeiroToken)
    {
        printf("\n");
    }

    primeiroToken = false;
}

int main() {
    yylex();
    return 0;
}