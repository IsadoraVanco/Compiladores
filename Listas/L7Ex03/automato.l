/* Não utilizar a biblioteca do flex*/
%option noyywrap
%{

%}


%%

(aba)+      printf("action 1\n");

ab*a        printf("action 2\n");

(a|b)       printf("action 3\n");

.           printf("error\n");

%%

int main() {
    yylex();
    return 0;
}