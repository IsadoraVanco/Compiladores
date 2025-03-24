# Linear Scan

O Linear Scan é um algoritmo proposto para a alocação de registradores. Este projeto consiste em fornecer uma entrada contendo o tempo ativo inicial e final de cada variável, e um valor máximo de registradores disponíveis (K). Depois, o algoritmo verifica quais registradores serão alocados para cada variável, e quais variáveis sofrerão Spill.

## Política de ordenação das variáveis

* Ordena pelo início do tempo de vida, de forma crescente
* Se duas variáveis iniciam no mesmo tempo, ordena pelo tempo final de forma crescente
* Caso duas variáveis possuam o mesmo tempo inicial e final de vida, mantém a ordem de inserção
* Registradores com mesmo identificador serão substituídos de acordo com cada nova redefinição

## Como executar 

Utilize uma entrada de texto padronizada
```
K=x
vrA --> a b
vrB --> c d
```

E para executar:
```
./linearscan < entrada.txt
```

## Testes

Alguns testes para verificar se o Linear Scan está funcionando como deveria. 

* **teste_linearscan** -> Script automatizado utilizando alguns casos de teste. Copie o arquivo `linearscan.zip` para dentro da pasta do teste e execute o script.
```
./testar_linearscan.sh
```

* **TestesBasicos** -> Testes feitos a mão, para testar com eles utilize:
```
./linearscan < caminho/do/teste.txt
```