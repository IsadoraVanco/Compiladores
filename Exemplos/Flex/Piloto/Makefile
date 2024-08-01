# Nome do arquivo gerado
PROJETO = piloto

# Arquivo .l
ARQL = piloto.l

# Compiladores
CC = gcc
LEX = flex

all: $(PROJETO)

$(PROJETO): lex.yy.c
	$(CC) lex.yy.c -o $(PROJETO) -lfl

lex.yy.c: $(ARQL)
	$(LEX) $(ARQL)

clean:
	rm $(PROJETO) lex.yy.c