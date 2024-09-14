# Exemplos em Bison

* **Calculadora** => Exemplo de uma calculadora simples em Bison, que reconhece números de um dígito

## Estrutura básica

```
// Primeiro bloco: DECLARAÇÕES

%{
// Aqui, declara-se constantes, variáveis e protótipos de funções
}%

// Aqui vão declarações de variáveis e definições regulares

%%

// Segundo bloco: REGRAS DE TRADUÇÕES

%%

// Terceiro bloco: FUNÇÕES AUXILIARES
// Precisa ter ao mínimo, a main()
```

* Utiliza-se $1, $2, $3 para referir o valor de um atributo respectivo do lado direito de uma produção. E $$ representa o não terminal do lado esquerdo da produção.

* Caso não haja nenhuma ação definida para uma produção com um único símbolo, implicitamente, a ação {$$ = $1} será realizada.

* É necessário definir ao menos três funções: 
```
int yylex(void);
int yyparser(void);
void yyerror(const char *);
```

## Como compilar ?

Para gerar o arquivo **arquivo.tab.c**:

```
bison arquivo.y
```

Depois, basta compilar normalmente:

```
gcc arquivo.tab.c -o arquivo
```

**OBS**: O pacote "bison" deve ser instalado no Linux

## Fontes

* [Judson Santiago](https://www.youtube.com/@JudSan)