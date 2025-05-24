#include <fcntl.h>      // open
#include <unistd.h>     // read, write, close, STDERR_FILENO
#include <stdio.h>      // dprintf
#include "funcoes.h"

#define TAMANHO_BUFFER 1024

void acrescenta(const char *origem, const char *destino) {
    int fd_origem = open(origem, O_RDONLY);
    if (fd_origem == -1) {
        dprintf(STDERR_FILENO, "Erro: Não foi possível abrir o ficheiro de origem '%s'\n", origem);
        return;
    }

    int fd_destino = open(destino, O_WRONLY | O_APPEND);
    if (fd_destino == -1) {
        dprintf(STDERR_FILENO, "Erro: Não foi possível abrir o ficheiro de destino '%s'\n", destino);
        close(fd_origem);
        return;
    }

    char buffer[TAMANHO_BUFFER];
    ssize_t bytes_lidos;

    while ((bytes_lidos = read(fd_origem, buffer, TAMANHO_BUFFER)) > 0) {
        ssize_t bytes_escritos = write(fd_destino, buffer, bytes_lidos);
        if (bytes_escritos != bytes_lidos) {
            dprintf(STDERR_FILENO, "Erro: Falha ao escrever no ficheiro de destino '%s'\n", destino);
            break;
        }
    }

    if (bytes_lidos == -1) {
        dprintf(STDERR_FILENO, "Erro: Falha ao ler o ficheiro de origem '%s'\n", origem);
    }

    close(fd_origem);
    close(fd_destino);
}