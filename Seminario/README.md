# Seminário de Compiladores

**Tema**: Loaders e Arquivos executáveis: exe, elf, etc...

**Dupla**: Isadora e Filipe Viotto

* Para rodar o exemplo de loaders:
```
gcc program.c -o program.bin
gcc loader.c -o loader
./loader ./program.bin
```

* Rodar o exemplo em hexadecimal:
    **Linux**:
    ```
    gcc hello.c -o hello
    xxd ./hello
    ```

    **Windows:** Super Hex Editor

* Rodar o exemplo de disassembler:
    **Windows:** IDA Freeware