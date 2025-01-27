#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para execvp

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo_binario>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo binário
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Obtém o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("Tamanho do arquivo: %ld bytes\n", file_size);

    // Aloca memória para o arquivo
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (buffer == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    // Lê o arquivo para a memória
    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != file_size) {
        printf("Erro ao ler o arquivo.\n");
        free(buffer);
        fclose(file);
        return 1;
    }

    printf("Arquivo carregado na memória.\n");
    printf("\n");

    // Executa o binário carregado (usando execvp)
    printf("Executando o binário...\n");
    fclose(file);
    free(buffer);

    char *exec_args[] = {argv[1], NULL};
    if (execvp(argv[1], exec_args) == -1) {
        perror("Erro ao executar o binário");
        return 1;
    }

    return 0;
}