%{
#include <iostream>

using std::cout;

int yylex(void);
int yyparser(void);
void yyerror(const char *);

void emitirErroSintatico(int erro);

// Tipos de erros
enum {TOKEN_INESPERADO, TOKEN_FALTANTE};
%}

%token QUIT SHOW RESET SET PLOT RPN ABOUT
%token SETTINGS H_VIEW V_VIEW AXIS ERASE INTEGRAL_STEPS
%token ON OFF

%token INTEGRATE SUM MATRIX SOLVE DETERMINANT LINEAR_SYS

%token PONTO_VIRGULA DOIS_PONTOS VIRGULA PARENTESES_ESQ PARENTESES_DIR COLCHETE_ESQ COLCHETE_DIR
%token IGUAL

%token NOVA_LINHA

%token NUM_REAL NUM_INT IDENTIFIER

%%

inicial     : config PONTO_VIRGULA
            | calcula PONTO_VIRGULA
            | ERRO                  { emitirErroSintatico(); }
            | QUIT                  { exit(0); }
            | NOVA_LINHA        
            ;

config      : SHOW SETTINGS 
            | RESET SETTINGS 
            | SET H_VIEW NUM_REAL DOIS_PONTOS NUM_REAL 
            | SET V_VIEW NUM_REAL DOIS_PONTOS NUM_REAL 
            | SET AXIS ON
            | SET AXIS OFF
            | PLOT 
            | PLOT PARENTESES_ESQ funcao PARENTESES_DIR 
            | SET ERASE PLOT OFF 
            | SET ERASE PLOT ON 
            | RPN PARENTESES_ESQ expressao PARENTESES_DIR
            | SET INTEGRAL_STEPS NUM_INT
            | ABOUT
            ;

calcula     : INTEGRATE PARENTESES_ESQ limites VIRGULA funcao PARENTESES_DIR
            | SUM PARENTESES_ESQ VIRGULA limites VIRGULA expressao PARENTESES_DIR
            | MATRIX IGUAL COLCHETE_ESQ COLCHETE_ESQ valor nValor COLCHETE_DIR nValores COLCHETE_DIR
            | SHOW MATRIX
            | SOLVE DETERMINANT
            | SOLVE LINEAR_SYS
            ;

nValores    : VIRGULA COLCHETE_ESQ valor nValor COLCHETE_DIR nValores
            | // Vazio
            ;

nValor      : VIRGULA valor nValor
            | // Vazio
            ;

valor       : NUM_INT
            | NUM_REAL
            ;

limites     : lim_inf DOIS_PONTOS lim_sup
            ;

lim_inf     :
            ;

lim_sup     :
            ;

funcao      :
            ;

expressao   :
            ;

%%

void emitirErroSintatico(int erro)
{
    
}

void yyerror(const char *)
{
    emitirErroSintatico();
}

int main()
{
    yyparse();
}