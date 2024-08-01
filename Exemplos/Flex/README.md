# Exemplos em Flex

* **Piloto** => Exemplo mais simples de flex, o basicão
* **Palavras** => Reconhecedor de classe de palavras
* **Parser** => Exemplo básico, utilizando parser junto com o léxico

## Estrutura básica

```
// Primeiro bloco: DECLARAÇÕES

%{
// Aqui, declara-se constantes, variáveis e protótipos de funções
// Tudo isso, vai direto para o arquivo lex.yy.cc / lex.yy.c
}%

// Aqui vão declarações de variáveis e definições regulares

%%

// Segundo bloco: REGRAS DE TRADUÇÕES

%%

// Terceiro bloco: FUNÇÕES AUXILIARES
```

## Fontes

* [Judson Santiago](https://www.youtube.com/watch?v=7_TX7OtLWe8)