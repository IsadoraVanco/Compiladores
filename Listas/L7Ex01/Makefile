# Nome do projeto
PROJETO = l7e1

# Pasta de saída para arquivos objeto e outros gerados
OUT = out

# Cria a pasta de saída se ela não existir
$(shell mkdir -p $(OUT))

# Arquivos .l
LEXER = automato.l

# Flex e GCC
FLEX = flex
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -fstack-protector-all -Werror=implicit-function-declaration -g

# Regra padrão
all: $(PROJETO)

# Regra para compilar o projeto
$(PROJETO): $(OUT)/lex.yy.o
	$(CC) $(CFLAGS) $(OUT)/lex.yy.o -o $(PROJETO)

# Regra para gerar lex.yy.c e compilar em lex.yy.o
$(OUT)/lex.yy.o: $(LEXER)
	$(FLEX) $<
	mv lex.yy.c $(OUT)/
	$(CC) $(CFLAGS) -c $(OUT)/lex.yy.c -o $@

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -rf $(PROJETO)
	rm -rf $(OUT)

# Regra para executar o programa
run: all
	./$(PROJETO)

# Regra para executar o programa com o Valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJETO)
