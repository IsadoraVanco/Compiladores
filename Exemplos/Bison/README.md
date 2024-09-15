# Exemplos em Bison

* **Calculadora** => Exemplo de uma calculadora simples em Bison, que reconhece números de um dígito e faz operações (+ *)
* **Plus** => Evolução da Calculadora, faz operações (+ - * /) e reconhece números negativos de ponto flutuante
* **PlusFlex** => A mesma aplicação de Plus, mas utilizando o Flex e Bison
* **PlusPlusFlex** => Evolução de PlusFlex, armazena variáveis criadas e faz as operações com elas

## Estrutura básica

```
// Primeiro bloco: DECLARAÇÕES

%{
// Aqui, declara-se constantes, variáveis e protótipos de funções
}%

// Aqui vão declarações de variáveis e definições regulares
// As precedências também são definidas aqui

%%

// Segundo bloco: REGRAS DE TRADUÇÕES

%%

// Terceiro bloco: FUNÇÕES AUXILIARES
// Precisa ter ao mínimo, a main()
```

* Utiliza-se $1, $2, $3 para referir o valor de um atributo respectivo do lado direito de uma produção. E $$ representa o não terminal do lado esquerdo da produção.

* Caso não haja nenhuma ação definida para uma produção com um único símbolo, implicitamente, a ação {$$ = $1} será realizada.

* O Bison aceita gramáticas ambíguas, mas provavelmente haverá conflitos. Para isso, o Bison oferece um mecanismo para tratar os conflitos: símbolos de associatividade e precedência.

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

Pode-se usar a opção **-v** para gerar um arquivo **arquivo.output** contendo a descrição de conflitos e uma tabela de como eles foram resolvidos. 

Para que os tokens criados no Bison sejam reconhecidos no Flex, utiliza-se **-d** na compilação do Bison, que gerará um arquivo **arquivo.tab.h**.

Depois, basta compilar normalmente:

```
gcc arquivo.tab.c -o arquivo
```

**OBS**: O pacote "bison" deve ser instalado no Linux

## Fontes

* [Judson Santiago](https://www.youtube.com/@JudSan)