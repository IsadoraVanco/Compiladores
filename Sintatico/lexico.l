%option noyywrap
%x COMMENT
%{
#include <iostream>
#include <queue>
#include <string>
#include "sintatico.tab.h"

#define MAX_ID 255

using std::cout;
using std::queue;
using std::string;

extern YYSTYPE yylval;

bool existeToken = false;

int numColunas = 1;
int numLinhas = 1;
int linhaComentario = 1;
int colunaComentario = 1;

// Armazena os warnings
queue<int> linhasWarning;
queue<int> colunasWarning;

// Tipos de erros
enum {TOKEN_DESCONHECIDO, ID_GRANDE, CMT_ABERTO};
// Tipos de warnings
enum {CMT_DUPLO};

// Protótipos de funções
void guardarSimbolo(string token);
void emitirWarning(int erro, int linha, int coluna);
void emitirErroLexico(int erro, int linha, int coluna);
void finalizarComentarioBloco();
void guardarWarningComentario();
void iniciarComentarioBloco();
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

void        numColunas += yyleng; return VOID;
int         numColunas += yyleng; return INT;
char        numColunas += yyleng; return CHAR;
return      numColunas += yyleng; return RETURN;
break       numColunas += yyleng; return BREAK;
switch      numColunas += yyleng; return SWITCH;
case        numColunas += yyleng; return CASE;
default     numColunas += yyleng; return DEFAULT;
do          numColunas += yyleng; return DO;
while       numColunas += yyleng; return WHILE;
for         numColunas += yyleng; return FOR;
if          numColunas += yyleng; return IF;
else        numColunas += yyleng; return ELSE;
typedef     numColunas += yyleng; return TYPEDEF;
struct      numColunas += yyleng; return STRUCT;
printf      numColunas += yyleng; return PRINTF;
scanf       numColunas += yyleng; return SCANF;
define      numColunas += yyleng; return DEFINE;
exit        numColunas += yyleng; return EXIT;

"+"         numColunas += yyleng; return PLUS; 
"-"         numColunas += yyleng; return MINUS;
"*"         numColunas += yyleng; return MULTIPLY;
"/"         numColunas += yyleng; return DIV;
"%"         numColunas += yyleng; return REMAINDER;
"++"        numColunas += yyleng; return INC;
"--"        numColunas += yyleng; return DEC;
"&"         numColunas += yyleng; return BITWISE_AND;
"|"         numColunas += yyleng; return BITWISE_OR;
"~"         numColunas += yyleng; return BITWISE_NOT;
"^"         numColunas += yyleng; return BITWISE_XOR;
"!"         numColunas += yyleng; return NOT;
"&&"        numColunas += yyleng; return LOGICAL_AND;
"||"        numColunas += yyleng; return LOGICAL_OR;
"=="        numColunas += yyleng; return EQUAL;
"!="        numColunas += yyleng; return NOT_EQUAL;
"<"         numColunas += yyleng; return LESS_THAN;
">"         numColunas += yyleng; return GREATER_THAN;
"<="        numColunas += yyleng; return LESS_EQUAL;
">="        numColunas += yyleng; return GREATER_EQUAL;
">>"        numColunas += yyleng; return R_SHIFT;
"<<"        numColunas += yyleng; return L_SHIFT;
"="         numColunas += yyleng; return ASSIGN;
"+="        numColunas += yyleng; return ADD_ASSIGN;
"-="        numColunas += yyleng; return MINUS_ASSIGN;
";"         numColunas += yyleng; return SEMICOLON;
","         numColunas += yyleng; return COMMA;
":"         numColunas += yyleng; return COLON;
"("         numColunas += yyleng; return L_PAREN;
")"         numColunas += yyleng; return R_PAREN;
"{"         numColunas += yyleng; return L_CURLY_BRACKET;
"}"         numColunas += yyleng; return R_CURLY_BRACKET;
"["         numColunas += yyleng; return L_SQUARE_BRACKET;
"]"         numColunas += yyleng; return R_SQUARE_BRACKET;
"?"         numColunas += yyleng; return TERNARY_CONDITIONAL;
"#"         numColunas += yyleng; return NUMBER_SIGN;
"->"        numColunas += yyleng; return POINTER;

{string}        guardarSimbolo("STRING");
{caracter}      guardarSimbolo("CHARACTER");

{num_octal}     guardarSimbolo("NUM_OCTAL");
{num_int}       guardarSimbolo("NUM_INTEGER");
{num_hexa}      guardarSimbolo("NUM_HEXA");

{id}        {
                if(yyleng > MAX_ID) {
                    emitirErroLexico(ID_GRANDE, numLinhas, numColunas);
                }else{
                    guardarSimbolo("IDENTIFIER");
                }
}

{espaco}        numColunas++;
{cmt_linha}     reiniciarColunas();
{nova_linha}    reiniciarColunas();

{ini_cmt}                   iniciarComentarioBloco();
<COMMENT>{nova_linha}       reiniciarColunas(); 
<COMMENT>{fim_cmt}          finalizarComentarioBloco();
<COMMENT>{ini_cmt}[\n]      guardarWarningComentario(); reiniciarColunas();
<COMMENT>{ini_cmt}[^/]      guardarWarningComentario();
<COMMENT><<EOF>>            emitirErroLexico(CMT_ABERTO, linhaComentario, colunaComentario);
<COMMENT>.                  numColunas += yyleng; 

.                           emitirErroLexico(TOKEN_DESCONHECIDO, numLinhas, numColunas); 

%%

void guardarSimbolo(string token)
{

}

void finalizarComentarioBloco()
{
    numColunas += yyleng; 
    BEGIN(INITIAL);

    while(!linhasWarning.empty()){
        emitirWarning(CMT_DUPLO, linhasWarning.front(), colunasWarning.front());

        linhasWarning.pop();
        colunasWarning.pop();
    }
}

void guardarWarningComentario()
{
    // Adiciona a linha e coluna no vetor 
    linhasWarning.push(numLinhas);
    colunasWarning.push(numColunas);

    numColunas += yyleng;
}

void iniciarComentarioBloco()
{
    // Vai para o estado de comentário
    BEGIN(COMMENT);

    linhaComentario = numLinhas;
    colunaComentario = numColunas;
    numColunas += yyleng;
}

void emitirWarning(int erro, int linha, int coluna)
{
    verificarPrimeiroToken();    

    if(erro == CMT_DUPLO){
        cout << "warning:" << linha << ":" << coluna << ": '/*' within block comment";
    }
}

void emitirErroLexico(int erro, int linha, int coluna)
{
    verificarPrimeiroToken();    

    cout << "error:lexical:" << linha << ":" << coluna;

    switch(erro)
    {
        case TOKEN_DESCONHECIDO:
            cout << yytext;
            numColunas += yyleng;
            break;
        case ID_GRANDE:
            cout << "identifier too long";
            numColunas += yyleng;
            break;
        case CMT_ABERTO:
            cout << "unterminated comment";
            break;
        default:
            break;
    }

    // Deve terminar quando encontrar um erro
    exit(EXIT_FAILURE);
}

void verificarPrimeiroToken()
{
    if(existeToken){
        cout << "\n";
    }

    existeToken = true;
}

void reiniciarColunas()
{
    numColunas = 1; 
    numLinhas++;
}