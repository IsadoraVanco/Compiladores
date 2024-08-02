/* Não utilizar a biblioteca do flex*/
%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int numLinhas = 1;
int numColunas = 1;
bool cmtAberto = false;

// Tipos de erros
enum {TOKEN_DESCONHECIDO, ID_GRANDE, CMT_ABERTO};
// Tipos de warnings
enum {CMT_DUPLO};

// Protótipos de funções
void retirarBordas(char *token);
void emitirWarning(int erro);
void emitirErro(int erro);
void analisarComentarioBloco();
void mostrarTokenValor(char *token);
void mostrarToken(char *token);
%}

/* Declarações regulares */
/* Gerais */
letra       [A-Za-z]
decimal     [0-9]
hexa        [0-9A-Fa-f]
octal       [0-7]
espaco      [ ]
nova_linha  \n

/* Definições */
id          [_]?{letra}({letra}|{decimal}|_)*
num_int     {decimal}+
num_octal   0[1-7]{octal}*
num_hexa    0[Xx]{hexa}+
string      ["](.)*["]
caracter    ['](.|\\[abfnrtv\'\"?0\\])[']

cmt_linha       [/][/](.)*"\n"
cmt_multi       [/][*](.|\n)*[*][/]    
cmt_multi_ini   [/][*](.)*(\n)*

%%

void        mostrarToken("VOID");
int         mostrarToken("INT");
char        mostrarToken("CHAR");
return      mostrarToken("RETURN");
break       mostrarToken("BREAK");
switch      mostrarToken("SWITCH");
case        mostrarToken("CASE");
default     mostrarToken("DEFAULT");
do          mostrarToken("DO");
while       mostrarToken("WHILE");
for         mostrarToken("FOR");
if          mostrarToken("IF");
else        mostrarToken("ELSE");
typedef     mostrarToken("TYPEDEF");
struct      mostrarToken("STRUCT");
printf      mostrarToken("PRINTF");
scanf       mostrarToken("SCANF");
define      mostrarToken("DEFINE");
exit        mostrarToken("EXIT");

"+"         mostrarToken("PLUS"); 
"-"         mostrarToken("MINUS");
"*"         mostrarToken("MULTIPLY");
"/"         mostrarToken("DIV");
"%"         mostrarToken("REMAINDER");
"++"        mostrarToken("INC");
"--"        mostrarToken("DEC");
"&"         mostrarToken("BITWISE_AND");
"|"         mostrarToken("BITWISE_ORn");
"~"         mostrarToken("BITWISE_NOT");
"^"         mostrarToken("BITWISE_XOR");
"!"         mostrarToken("NOT");
"&&"        mostrarToken("LOGICAL_AND");
"||"        mostrarToken("LOGICAL_OR");
"=="        mostrarToken("EQUAL");
"!="        mostrarToken("NOT_EQUAL");
"<"         mostrarToken("LESS_THAN");
">"         mostrarToken("GREATER_THAN");
"<="        mostrarToken("LESS_EQUAL");
">="        mostrarToken("GREATER_EQUAL");
">>"        mostrarToken("R_SHIFT");
"<<"        mostrarToken("L_SHIFT");
"="         mostrarToken("ASSIGN");
"+="        mostrarToken("ADD_ASSIGN");
"-="        mostrarToken("MINUS_ASSIGN");
";"         mostrarToken("SEMICOLON");
","         mostrarToken("COMMA");
":"         mostrarToken("COLON");
"("         mostrarToken("L_PAREN");
")"         mostrarToken("R_PAREN");
"{"         mostrarToken("L_CURLY_BRACKET");
"}"         mostrarToken("R_CURLY_BRACKET");
"["         mostrarToken("L_SQUARE_BRACKET");
"]"         mostrarToken("R_SQUARE_BRACKET");
"?"         mostrarToken("TERNARY_CONDITIONAL");
"#"         mostrarToken("NUMBER_SIGN");
"->"        mostrarToken("POINTER");

{id}        {
                if(yyleng > 255) {
                    emitirErro(ID_GRANDE);
                }else{
                    mostrarTokenValor("IDENTIFIER");
                }
}

{string}        retirarBordas("STRING");
{caracter}      retirarBordas("CHARACTER");

{num_octal}     mostrarTokenValor("NUM_OCTAL");
{num_int}       mostrarTokenValor("NUM_INTEGER");
{num_hexa}      mostrarTokenValor("NUM_HEXA");

{espaco}        numColunas++;
{cmt_linha}     numColunas = 1; numLinhas++;
{nova_linha}    numColunas = 1; numLinhas++;
{cmt_multi}     analisarComentarioBloco(); 
{cmt_multi_ini} emitirErro(CMT_ABERTO); return 0;

.               emitirErro(TOKEN_DESCONHECIDO); 

%%

void retirarBordas(char *token)
{
    char novaString[yyleng];

    // Copia sem os caracteres das bordas
    int j = 0;
    for (int i = 1; yytext[i] != '\0'; ++i) {
        novaString[j++] = yytext[i];
    }
    novaString[--j] = '\0';

    printf("%s(%s)\n", token, novaString);
}

void analisarComentarioBloco(){
    numColunas++;
    for(int i = 1; i < yyleng; i++){
        if(yytext[i] == '\n'){
            numLinhas++;
            numColunas = 1;
        }else{
            if(yytext[i] == '/' && yytext[i + 1] == '*'){
                emitirWarning(CMT_DUPLO);
            }
            numColunas++;
        }
    }
}

void emitirWarning(int erro)
{
    printf("warning:lexical:%d:%d: ", numLinhas, numColunas);

    switch(erro)
    {
        case CMT_DUPLO:
            printf("'/*' within block comment\n");
            break;
        default:
            break;
    }
}

void emitirErro(int erro)
{
    printf("error:lexical:%d:%d: ", numLinhas, numColunas);

    switch(erro)
    {
        case TOKEN_DESCONHECIDO:
            printf("%s\n", yytext);
            numColunas += yyleng;
            break;
        case ID_GRANDE:
            printf("identifier too long\n");
            numColunas += yyleng;
            break;
        case CMT_ABERTO:
            printf("unterminated comment\n");
            break;
        default:
            break;
    }
}

void mostrarTokenValor(char *token)
{
    printf("%s(%s)\n", token, yytext);

    numColunas += yyleng;
}

void mostrarToken(char *token)
{
    printf("%s\n", token);

    numColunas += yyleng;
}

int main() 
{
    yylex();
    return 0;
}