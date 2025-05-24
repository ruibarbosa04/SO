#include <fcntl.h>      // open
#include <unistd.h>     // read, write, close, STDERR_FILENO
#include <stdio.h>      // dprintf
#include "funcoes.h"

#define TAMANHO_BUFFER 1024

void mostra_ficheiro(const char* nome_ficheiro) {
    int fd = open(nome_ficheiro, O_RDONLY);  // Tenta abrir o ficheiro em modo leitura

    if (fd == -1) {
        dprintf(STDERR_FILENO, "Erro: Não foi possível abrir o ficheiro '%s'\n", nome_ficheiro);
        return;
    }

    char buffer[TAMANHO_BUFFER];
    ssize_t bytes_lidos;

    // Lê o ficheiro e escreve no stdout
    while ((bytes_lidos = read(fd, buffer, TAMANHO_BUFFER)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_lidos);
    }

    if (bytes_lidos == -1) {
        dprintf(STDERR_FILENO, "Erro: Ocorreu um erro durante a leitura do ficheiro.'%s'\n", nome_ficheiro);
    }

    close(fd);
}