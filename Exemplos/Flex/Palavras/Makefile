# Nome do arquivo gerado
PROJETO = palavras

# Arquivo .l
ARQL = palavras.l

# Compiladores
CC = g++
LEX = flex++
FLAGS = -std=c++17

all: $(PROJETO)

$(PROJETO): lex.yy.cc
	$(CC) lex.yy.cc -o $(PROJETO) $(FLAGS)

lex.yy.cc: $(ARQL)
	$(LEX) $(ARQL)

clean:
	rm $(PROJETO) lex.yy.cc