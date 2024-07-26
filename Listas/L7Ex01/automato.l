/* Não utilizar a biblioteca do flex*/
%option noyywrap
%{

%}

%%

[a-z]+[a-z0-9]* { 
    printf("%s\n", yytext);  
}

[0-9]+ { 
    printf("%s\n", yytext);  
}

[0-9]+e[+|-]?[0-9]+ { 
    printf("%s\n", yytext);  
}

[+|-] { 
    printf("%s\n", yytext);  
}

\n {}

<<EOF>> { return 0; }

. { 
    printf("ERRO\n");  
}

%%

int main() {
    yylex();
    return 0;
}