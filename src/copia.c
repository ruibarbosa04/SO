#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "funcoes.h"

#define TAMANHO_BUFFER 1024

void copia_ficheiro(const char *ficheiro) {
    int fd_in = open(ficheiro, O_RDONLY);
    if (fd_in < 0) {
        dprintf(2, "Erro: ficheiro '%s' não existe ou não pode ser aberto\n", ficheiro);
        return;
    }

    char nome_copia[1024];
    snprintf(nome_copia, sizeof(nome_copia), "%s.copia", ficheiro);

    int fd_out = open(nome_copia, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        dprintf(2, "Erro: não foi possível criar '%s'\n", nome_copia);
        close(fd_in);
        return;
    }

    char buf[TAMANHO_BUFFER];
    ssize_t bytes_lidos;
    while ((bytes_lidos = read(fd_in, buf, TAMANHO_BUFFER)) > 0) {
        ssize_t bytes_escritos = write(fd_out, buf, bytes_lidos);
        if (bytes_escritos != bytes_lidos) {
            dprintf(2, "Erro ao escrever em '%s'\n", nome_copia);
            break;
        }
    }
    if (bytes_lidos < 0)
        dprintf(2, "Erro ao ler o ficheiro '%s'\n", ficheiro);

    close(fd_in);
    close(fd_out);
}