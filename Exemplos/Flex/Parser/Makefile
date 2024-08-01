# Nome do arquivo gerado
PROJETO = parser

# ******** ARQUIVOS **********************************

# Arquivos c/c++
CXX_SRCS = parser.cpp main.cpp
CXX_HEADERS = tokens.h parser.h

# Arquivos flex
LEX_SRCS = lexico.l
LEX_GNRT = lex.yy.cc

# ******** COMPILADORES E FLAGS **********************************

# Compiladores
CXX = g++
LEX = flex

# Flags dos compiladores
CXX_FLAGS = -std=c++17 -O2
LEX_FLAGS = -lfl

# ******** DIRETORIOS **********************************

# Pasta de destino do build
BUILD_DIR = build

# ******** REGRAS DE COMPILAÇÃO **********************************

# Regra padrão para o comando "make"
all: $(PROJETO)

# Compilar o flex gerado
$(LEX_GNRT): $(LEX_SRCS)
	$(LEX) -o $@ $<

# Compilar o executável
$(PROJETO): $(CXX_SRCS) $(CXX_HEADERS) $(LEX_GNRT)
	$(CXX) $^ $(CXX_FLAGS) $(LEX_FLAGS) -o $@

# Limpa os arquivos gerados
clean:
	rm -f $(PROJETO) $(LEX_GNRT) *.o