cmake_minimum_required(VERSION 3.0.0)
# Nome da pasta
project(Palavras)

# Configuração do C++
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

# Configuração do flex
# Encontra a biblioteca do flex
find_package(FLEX REQUIRED)
# nomeAlvo arquivoFonte diretorioDestino flags (-+ é --c++)
FLEX_TARGET(Lexer palavras.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc COMPILE_FLAGS "-+")
# Incluir o diretorioDestino no cmake
include_directories(${CMAKE_BINARY_DIR})

# Gera o executável a partir das saídas do nomeAlvo
add_executable(palavras ${FLEX_Lexer_OUTPUTS})

# Como executar:
# cmake ../Palavras
# OU
# cmake -S .