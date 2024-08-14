/* Não utilizar a biblioteca do flex*/
%option noyywrap
%x COMMENT
%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ID 255

bool existeToken = false;
int numColunas = 1;
int numLinhas = 1;
int linhaComentario = 1;
int colunaComentario = 1;

// Armazena os warnings
int tamanhoWarning = -1;
int colunasWarning[10];
int linhasWarning[10];

// Tipos de erros
enum {TOKEN_DESCONHECIDO, ID_GRANDE, CMT_ABERTO};
// Tipos de warnings
enum {CMT_DUPLO};

// Protótipos de funções
void mostrarTexto(char *token);
void emitirWarning(int erro, int linha, int coluna);
void emitirErro(int erro, int linha, int coluna);
void finalizarComentarioBloco();
void guardarWarningComentario();
void iniciarComentarioBloco();
void mostrarTokenValor(char *token);
void mostrarToken(char *token);
void verificarPrimeiroToken();
void reiniciarColunas();
%}

/* Declarações regulares */
/* Gerais */
letra       [A-Za-z]
decimal     [0-9]
hexa        [0-9A-Fa-f]
octal       [0-7]
espaco      [ ]
nova_linha  \n
ini_cmt     [/][*]
fim_cmt     [*][/]

/* Definições */
id          ({letra}|_)+({letra}|{decimal}|_)*
num_int     {decimal}+
num_octal   0[1-7]{octal}*
num_hexa    0[Xx]{hexa}+
string      ["](\\.|[^\"])*["]
caracter    [']([^\n\'\\]|\\[abfrtnv\'\"?0\\])[']

cmt_linha       [/][/](.)*("\n")?

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

{string}        mostrarTexto("STRING");
{caracter}      mostrarTexto("CHARACTER");

{num_octal}     mostrarTokenValor("NUM_OCTAL");
{num_int}       mostrarTokenValor("NUM_INTEGER");
{num_hexa}      mostrarTokenValor("NUM_HEXA");

{id}        {
                if(yyleng > MAX_ID) {
                    emitirErro(ID_GRANDE, numLinhas, numColunas);
                }else{
                    mostrarTokenValor("IDENTIFIER");
                }
}

{espaco}        numColunas++;
{cmt_linha}     reiniciarColunas();
{nova_linha}    reiniciarColunas();

{ini_cmt}                iniciarComentarioBloco();
<COMMENT>.{fim_cmt}      finalizarComentarioBloco();
<COMMENT>{ini_cmt}       guardarWarningComentario();
<COMMENT>{nova_linha}    reiniciarColunas();
<COMMENT><<EOF>>         emitirErro(CMT_ABERTO, linhaComentario, colunaComentario); return 0;
<COMMENT>.               numColunas += yyleng;

.               emitirErro(TOKEN_DESCONHECIDO, numLinhas, numColunas); 

%%

void mostrarTexto(char *token)
{
    char novaString[yyleng];

    // Copia sem os caracteres das bordas
    int j = 0;
    for (int i = 1; yytext[i] != '\0'; ++i) {
        novaString[j++] = yytext[i];
    }
    novaString[--j] = '\0';

    numColunas += yyleng;

    verificarPrimeiroToken();    

    printf("%s(%s)", token, novaString);
}

void finalizarComentarioBloco()
{
    numColunas += yyleng; 
    BEGIN(INITIAL);

    if(tamanhoWarning >= 0){
        for(int i = 0; i <= tamanhoWarning; i++){
            emitirWarning(CMT_DUPLO, linhasWarning[i], colunasWarning[i]);
        }
        tamanhoWarning = -1;
    }
}

void guardarWarningComentario()
{
    // Adiciona a linha e coluna no vetor 
    tamanhoWarning++;
    linhasWarning[tamanhoWarning] = numLinhas;
    colunasWarning[tamanhoWarning] = numColunas;

    numColunas += yyleng;
}

void iniciarComentarioBloco()
{
    // Vai para o estado de comentário
    BEGIN(COMMENT);

    linhaComentario = numLinhas;
    colunaComentario = numColunas;
    numColunas += yyleng;
    tamanhoWarning = -1;
}

void emitirWarning(int erro, int linha, int coluna)
{
    verificarPrimeiroToken();    

    if(erro == CMT_DUPLO){
        printf("warning:%d:%d: '/*' within block comment", linha, coluna);
    }
}

void emitirErro(int erro, int linha, int coluna)
{
    verificarPrimeiroToken();    

    printf("error:lexical:%d:%d: ", linha, coluna);

    switch(erro)
    {
        case TOKEN_DESCONHECIDO:
            printf("%s", yytext);
            numColunas += yyleng;
            break;
        case ID_GRANDE:
            printf("identifier too long");
            numColunas += yyleng;
            break;
        case CMT_ABERTO:
            printf("unterminated comment");
            break;
        default:
            break;
    }
}

void mostrarTokenValor(char *token)
{
    verificarPrimeiroToken();    

    printf("%s(%s)", token, yytext);
    numColunas += yyleng;
}

void mostrarToken(char *token)
{
    verificarPrimeiroToken();

    printf("%s", token);
    numColunas += yyleng;
}

void verificarPrimeiroToken()
{
    if(existeToken){
        printf("\n");
    }

    existeToken = true;
}

void reiniciarColunas()
{
    numColunas = 1; 
    numLinhas++;
}

int main() 
{
    yylex();
    return 0;
}