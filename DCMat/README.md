# DCMat

Projeto de uma calculadora gráfica que permite alterar configurações, definir variáveis, fazer cálculos e mostrar funções.

## Funções do programa

Configurações:
* `about;` -> Mostra os créditos do programa
* `quit;` -> Fecha o programa
* `show settings;` -> Mostra as configurações
* `set axis on;` -> Habilita o desenho dos eixos de coordenadas
* `set axis off;` -> Desabilita o desenho dos eixos de coordenadas
* `set erase plot on;` -> Habilita a limpeza do desenho de funções já mostradas
* `set erase plot off;` -> Desabilita a limpeza do desenho de funções já mostradas
* `set connect_dots on;` -> Habilita o algoritmo de desenhar pontos ligados
* `set connect_dots off;` -> Desabilita o algoritmo de desenhar pontos ligados
* `set float precision 1;` -> Configura o número de casas de precisão dos resultados
* `set integral_steps 1;` -> Configura o número de passos para a somatória da integral
* `set h_view 1.2:1.4;` -> Configura os limites de visualização do gráfico do eixo x
* `set v_view 1.2:1.4;` -> Configura os limites de visualização do gráfico do eixo y
* `matrix = [[1,2],[3,4]];` -> Configura uma matriz padrão

Símbolos:
* `show symbols;` -> Mostra todos os símbolos e quais seus tipos
* `show matrix;` -> Mostra a matriz padrão
* `a;` -> Mostra o valor do símbolo
* `a = [[1,2],[3,4]];` -> Atribui uma matriz para um símbolo
* `b = sen(0);` -> Atribui o valor de uma expressão para um símbolo

Cálculos:
* `sum(a, 0.1:2, a + 1);` -> Calcula o somatório da expressão considerando a variável e o intervalo 
* `integrate(0:5, x + 1);` -> Calcula o valor da integral no intervalo 
* `rpn(a+b * c^2);` -> Mostra a ordem dos elementos dentro da árvore de operações da expressão 
* `solve determinant;` -> Resolve o determinante da matriz padrão definida
* `solve linear_system;` -> Resolve o sistema linear da matriz padrão definida
* `a - e / b * sen(-pi)` -> Mostra o valor da expressão

Funções:
* `plot(x^2 - b);` -> Mostra o gráfico da função

## Como executar

Utilize o comando:
```
./dcmat
```

## Pendentes

Algumas funções estão incompletas...

### Tarefas

1. Separar matriz e métodos em uma classe
2. Transformar gráficos em uma classe
3. Testar colocar uma variável nas definições
4. Leak de memória de algum token do léxico quando há erro
5. Leak de memória de nodes criados quando há erro
6. Modificar addSymbol para apenas matriz
7. Adicionar connect_dots
8. Adicionar operações com matrizes

### Dúvidas

1. Matrix recebe variaveis como valores?
2. Mostrar valor da matriz na expressão (>id;)?
