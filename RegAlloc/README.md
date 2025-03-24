# RegAlloc

Projeto de alocação de registradores usando Coloração de Grafos. Este projeto consiste em fornecer uma entrada contendo o número identificador de um grafo de interferência, um valor máximo de registradores disponíveis (K) e as associações de variáveis. Depois, o algoritmo verifica quais registradores serão alocados para cada variável, e quais variáveis sofrerão Spill.

## Como executar 

Utilize uma entrada de texto padronizada
```
Grafo x:
K=y
A --> B D
B --> C A
C --> B
D --> A
```

**OBS**: variáveis com valores abaixo de y, serão considerados como registradores físicos já alocados.

E para executar:
```
./regalloc < entrada.txt
```

## Testes

Alguns testes para verificar se o RegAlloc está funcionando como deveria. 

* **teste_regalloc** -> Script automatizado utilizando alguns casos de teste. Copie o arquivo `regalloc.zip` para dentro da pasta do teste e execute o script.
```
./testar_regalloc.sh
```

* **TestesBasicos** -> Testes feitos a mão, rode eles com:
```
./regalloc < caminho/do/teste.txt
```