/* Não utilizar a biblioteca do flex*/
%option noyywrap
%{
#include <stdbool.h>

bool primeiroToken = true;

void mostrarComentario();
void mostrarTokenValor(char *token);
void mostrarToken(char *token);
void verificarPrimeiroToken();
%}

decimal [0-9]
letra   [a-z]
espaco  [ ]

id      {letra}+[{letra}{decimal}]*
real    {decimal}*[.]{decimal}+
num     {decimal}+
cmt     --{letra}*[\n]

%%

if          mostrarToken("IF");  

{id}        mostrarTokenValor("ID");

{espaco}    mostrarToken("white space");

{num}       mostrarTokenValor("NUM");

{real}      mostrarTokenValor("REAL");

{cmt}       mostrarComentario();

\n          ;

.           mostrarTokenValor("error");

%%

void mostrarComentario()
{
    verificarPrimeiroToken();

    char novaString[yyleng];

    for(int i = 0; i < yyleng - 1; i++){
        novaString[i] = yytext[i];
    }

    novaString[yyleng - 1] = '\0';

    printf("%s comment", novaString);
}

void mostrarTokenValor(char *token)
{
    verificarPrimeiroToken();

    printf("%s %s", yytext, token);
}

void mostrarToken(char *token)
{
    verificarPrimeiroToken();

    printf("%s", token);
}

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