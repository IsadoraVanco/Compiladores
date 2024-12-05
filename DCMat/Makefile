# Nome do arquivo gerado
PROJETO = dcmat

# ******** ARQUIVOS **********************************

# Arquivos c/c++
CXX_SRCS = main.cpp dcmat.cpp ast.cpp graphics.cpp
CXX_HEADERS = dcmat.h types.h ast.h graphics.h

# Arquivos flex
LEX_SRCS = lexico.l
LEX_GNRT = lex.yy.c

# Arquivos Bison
BIS_SRCS = sintatico.y
BIS_GNRT = sintatico.tab.c
BIS_OUT = tokens.h

# Arquivos extras
MAKEFILE = Makefile

# ******** COMPILADORES E FLAGS **********************************

# Compiladores
CXX = g++
LEX = flex
BIS = bison

# Flags dos compiladores
CXX_FLAGS = -std=c++17 -O2
LEX_FLAGS = -lfl
BIS_FLAGS = -d

# ******** REGRAS DE COMPILAÇÃO **********************************

# Regra padrão para o comando "make"
all: $(PROJETO)

# Compilar o executável
$(PROJETO): $(LEX_GNRT) $(BIS_GNRT) $(CXX_SRCS) $(CXX_HEADERS)
	$(CXX) $^ $(CXX_FLAGS) $(LEX_FLAGS) -I. -o $@

# Compilar o flex gerado
$(LEX_GNRT): $(LEX_SRCS)
	$(LEX) -o $@ $<

# Compilar o bison gerado
$(BIS_GNRT): $(BIS_SRCS)
	$(BIS) $(BIS_FLAGS) $(BIS_SRCS)

# Compilar os arquivos fontes
%.o: %.cpp $(CXX_HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@	

# Limpa os arquivos gerados
clean:
	rm -f $(PROJETO) $(LEX_GNRT) $(BIS_GNRT) $(BIS_OUT) *.o $(PROJETO).zip

# Limpa o terminal e roda o código
run: $(PROJETO)
	clear
	./$(PROJETO)

# Limpa o terminal e roda o código com Valgrind
valgrind: $(PROJETO)
	clear
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJETO)

# Compactar o projeto em um arquivo ZIP
zip:
	zip $(PROJETO).zip $(CXX_SRCS) $(CXX_HEADERS) $(LEX_SRCS) $(BIS_SRCS) $(MAKEFILE)