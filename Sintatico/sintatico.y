%{
#include <iostream>

using std::cout;

int yylex(void);
int yyparser(void);
void yyerror(const char *);

extern void verificarPrimeiroToken();

void emitirErroSintatico(int erro);

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
%}

%union {
    struct {
        char *valor;
        int column;
        int line;
        int type;
    } token;
}

%token IDENTIFIER

%token STRING CHARACTER

%token NUM_HEXA NUM_INTEGER NUM_OCTAL

%token VOID INT CHAR RETURN BREAK
%token SWITCH CASE DEFAULT DO WHILE
%token FOR IF ELSE TYPEDEF STRUCT
%token PRINTF SCANF DEFINE EXIT

%token PLUS MINUS MULTIPLY DIV REMAINDER
%token INC DEC BITWISE_AND BITWISE_OR BITWISE_NOT
%token BITWISE_XOR NOT LOGICAL_AND LOGICAL_OR EQUAL
%token NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token R_SHIFT L_SHIFT ASSIGN ADD_ASSIGN MINUS_ASSIGN
%token SEMICOLON COMMA COLON L_PAREN R_PAREN
%token L_CURLY_BRACKET R_CURLY_BRACKET L_SQUARE_BRACKET R_SQUARE_BRACKET TERNARY_CONDITIONAL
%token NUMBER_SIGN POINTER

%%

inicial     : programa EoF              { cout << "SUCCESSFUL COMPILATION."; }
            | programa ERRO             { emitirErroSintatico(); }
            ;

programa    : declaracoes nPrograma     
            | funcao nPrograma     
            ;

nPrograma   : programa
            | // Vazia
            ;

declaracoes : NUMBER_SIGN DEFINE IDENTIFIER expressao
            | dVariaveis
            | dPrototipos
            ;

funcao      : tipo ponteiro IDENTIFIER parametros L_CURLY_BRACKET bFuncao comandos R_CURLY_BRACKET
            ;

bFuncao     : dVariaveis bFuncao
            | // Vazia
            ;

ponteiro    : MULTIPLY ponteiro
            | // Vazia
            ;

expressao   : eAtribuicao
            | expressao COMMA eAtribuicao
            ;

dVariaveis  : tipo bVariaveis SEMICOLON
            ;

bVariaveis : ponteiro IDENTIFIER bColchete bAtribui nVariaveis
            ;

nVariaveis : COMMA bVariaveis
            | // Vazia
            ;

bColchete : L_SQUARE_BRACKET expressao R_SQUARE_BRACKET bColchete
            | /// Vazia
            ;

bAtribui    : ASSIGN eAtribuicao
            | // Vazia
            ;

dPrototipos : tipo ponteiro IDENTIFIER parametros SEMICOLON
            ;

tipo        : INT
            | CHAR
            | VOID 
            ;

parametros  : L_PAREN dIdentifier R_PAREN
            ;

dIdentifier : tipo ponteiro IDENTIFIER bColchete nIdentifier
            ;

nIdentifier : COMMA dIdentifier
            | // Vazia
            ;

comandos    : lComandos nComandos
            ;

nComandos   : comandos
            | // Vazia
            ;

eAtribuicao : eCondicional
            | eUnaria operacao eAtribuicao
            ;

operacao    : ASSIGN
            | ADD_ASSIGN
            | MINUS_ASSIGN
            ;

lComandos   : DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON
            | IF L_PAREN expressao R_PAREN bloco blocoElse
            | WHILE L_PAREN expressao R_PAREN bloco
            | FOR L_PAREN bExpressao SEMICOLON bExpressao SEMICOLON bExpressao R_PAREN bloco
            | PRINTF L_PAREN STRING blocoPrint R_PAREN SEMICOLON
            | SCANF L_PAREN COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON
            | EXIT L_PAREN expressao R_PAREN SEMICOLON
            | RETURN bExpressao SEMICOLON
            | expressao SEMICOLON
            | SEMICOLON
            | bloco
            ;

blocoElse   : ELSE bloco
            | // Vazia
            ;

bExpressao  : expressao 
            | // Vazia
            ;

blocoPrint  : COMMA expressao
            | // Vazia
            ;

eCondicional: eOrLogico orTernario
            ;

orTernario  : TERNARY_CONDITIONAL expressao COLON eCondicional
            | // Vazia
            ;

eUnaria     : ePosFixa
            | INC eUnaria
            | DEC eUnaria
            | BITWISE_AND eCast
            | MULTIPLY eCast
            | PLUS eCast
            | MINUS eCast
            | BITWISE_NOT eCast
            | NOT eCast
            ;

bloco       : L_CURLY_BRACKET comandos R_CURLY_BRACKET
            ;

eOrLogico   : eAndLogico
            : eOrLogico LOGICAL_OR eAndLogico
            ;

ePosFixa    : ePrimaria
            | ePosFixa L_SQUARE_BRACKET expressao R_SQUARE_BRACKET
            | ePosFixa INC 
            | ePosFixa DEC
            | ePosFixa L_PAREN bPosFixa R_PAREN
            ;

bPosFixa    : eAtribuicao nPosFixa
            | // Vazia
            ;

nPosFixa    : COMMA bPosFixa
            ;

eCast       : eUnaria
            | L_PAREN tipo ponteiro R_PAREN eCast
            ;

eAndLogico  : eOr
            | eAndLogico LOGICAL_AND eOr 
            ;

ePrimaria   : IDENTIFIER
            | numero
            | CHARACTER
            | STRING
            | L_PAREN expressao R_PAREN
            ;

eOr         : eXor 
            | eOr BITWISE_OR eXor
            ;

numero      : NUM_INTEGER
            | NUM_HEXA
            | NUM_OCTAL
            ;

eXor        : eAnd 
            | eXor BITWISE_XOR eAnd 
            ;

eAnd        : eIgual 
            | eAnd BITWISE_AND eIgual 
            ;

eIgual      : eRelacional 
            | eIgual EQUAL eRelacional
            | eIgual NOT_EQUAL eRelacional
            ;

eRelacional : eShift
            | eRelacional LESS_THAN eAditiva
            | eRelacional LESS_EQUAL eAditiva
            | eRelacional GREATER_THAN eAditiva
            | eRelacional GREATER_EQUAL eAditiva
            ;

eShift      : eAditiva
            | eShift R_SHIFT eAditiva
            | eShift L_SHIFT eAditiva
            ;

eAditiva    : eMulti
            | eAditiva PLUS eMulti
            | eAditiva MINUS eMulti
            ;

eMulti      : eCast
            | eMulti MULTIPLY eCast
            | eMulti DIV eCast
            | eMulti REMAINDER eCast
            ;

%%

void emitirErroSintatico(int erro)
{
    extern int numColunas;
    extern int numLinhas;

    verificarPrimeiroToken();

    cout << "error:syntax:" << numLinhas << ":" << numColunas;

    switch(erro)
    {
        case TOKEN_INESPERADO:

        break;
        
        case TOKEN_FALTANTE:
        break;

        default:
        break;
    };

    exit(EXIT_FAILURE);
}

void yyerror(const char *)
{
    emitirErroSintatico(TOKEN_FALTANTE);
}

int main()
{
    yyparse();
}