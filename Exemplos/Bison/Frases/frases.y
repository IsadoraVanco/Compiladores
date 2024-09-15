%{
#include <iostream>

using std::cout;

int yylex(void);
int yyparser(void);
void yyerror(const char *);
%}

%token ADJETIVO SUBSTANTIVO INTERJEICAO CONJUNCAO PREPOSICAO ADVERBIO ARTIGO NUMERAL PRONOME VERBO

%%

texto   : texto frase
        | frase
        ;

frase   : sujeito VERBO objeto      { cout << "Frase correta\n"; }
        ;

sujeito : PRONOME                   // $$ = $1
        | ARTIGO SUBSTANTIVO        // $$ = $1
        ;

objeto  : ARTIGO SUBSTANTIVO        // $$ = $1
        | ADJETIVO                  // $$ = $1
        | ADVERBIO                  // $$ = $1
        ;

%%

// Nome do arquivo externo definido pelo flex
extern FILE *yyin;

void yyerror(const char *string)
{
    extern int yylineno;
    extern char *yytext;

    cout << "[ERRO] " << string << "\n";
    cout << "Simbolo: " << yytext << "\n";
    cout << "Linha: " << yylineno << "\n";
    // exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    // Caso um arquivo seja passado por argumento, lê ele
    if(argc > 1)
    {
        FILE *arquivo;
        arquivo = fopen(argv[1], "r");

        if(!arquivo)
        {
            printf("Arquivo não encontrado: %s\n", argv[1]);
            printf("Lendo do teclado...\n\n");
        }
        else
        {
            yyin = arquivo;
        }
    }

    yyparse();
}