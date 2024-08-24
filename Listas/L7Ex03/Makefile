# Nome do arquivo gerado
PROJETO = l7e3

# ******** ARQUIVOS **********************************

# Arquivos c/c++
CXX_SRCS = 
CXX_HEADERS = 

# Arquivos flex
LEX_SRCS = automato.l
LEX_GNRT = lex.yy.c

# ******** COMPILADORES E FLAGS **********************************

# Compiladores
CXX = gcc
LEX = flex

# Flags dos compiladores
CXX_FLAGS =
LEX_FLAGS = -lfl

# ******** REGRAS DE COMPILAÇÃO **********************************

# Regra padrão para o comando "make"
all: $(PROJETO)

# Compilar o flex gerado
$(PROJETO): $(LEX_GNRT) $(CXX_SRCS) $(CXX_HEADERS)
	$(CXX) $^ $(CXX_FLAGS) $(LEX_FLAGS) -o $@

# Compilar o flex gerado
$(LEX_GNRT): $(LEX_SRCS)
	$(LEX) -o $@ $<

# Limpa os arquivos gerados
clean:
	rm -f $(PROJETO) $(LEX_GNRT) *.o