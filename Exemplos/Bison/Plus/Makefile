# Nome do arquivo gerado
PROJETO = plus

# ******** ARQUIVOS **********************************

# Arquivos c/c++
CXX_SRCS = 
CXX_HEADERS = 

# Arquivos flex
LEX_SRCS = 
LEX_GNRT =

# Arquivos Bison
BIS_SRCS = plus.y
BIS_GNRT = plus.tab.c
BIS_OUT = plus.output

# ******** COMPILADORES E FLAGS **********************************

# Compiladores
CXX = g++
LEX = flex
BIS = bison

# Flags dos compiladores
CXX_FLAGS = -std=c++17 -O2
LEX_FLAGS = -lfl
BIS_FLAGS = -v

# ******** REGRAS DE COMPILAÇÃO **********************************

# Regra padrão para o comando "make"
all: $(PROJETO)

# Compilar o executável
$(PROJETO): $(LEX_GNRT) $(BIS_GNRT) $(CXX_SRCS) $(CXX_HEADERS)
	$(CXX) $^ $(CXX_FLAGS) $(LEX_FLAGS) -o $@

# Compilar o flex gerado
$(LEX_GNRT): $(LEX_SRCS)
	$(LEX) -o $@ $<

# Compilar o bison gerado
$(BIS_GNRT): $(BIS_SRCS)
	$(BIS) $(BIS_SRCS) $(BIS_FLAGS)

# Compilar os arquivos fontes
%.o: %.cpp $(CXX_HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@	

# Limpa os arquivos gerados
clean:
	rm -f $(PROJETO) $(LEX_GNRT) $(BIS_GNRT) $(BIS_OUT) *.o