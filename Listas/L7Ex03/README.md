# Exercicio 03 - Lista 07

Créditos ao profº Wesley Attrot, autor do exercicio.

Utilizando a ferramenta Flex, escreva um arquivo l para gerar um analisador léxico que aceita as cadeias geradas pelas expressões regulares a seguir, as quais estão apresentadas em ordem de prioridade (da maior para a menor):

```
(aba)+      (action 1)
(a(b*)a)    (action 2)
(a|b)       (action 3)
```

Com o programa gerado, reconheça os tokens na entrada **abaabbaba** e diga ao final do reconhecimento como cada token é classificado, isto é: (action 1), (action 2) ou (action 3)