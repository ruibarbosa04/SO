/**
 * @file lista.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "funcoes.h"

/**
 * @brief Lista o conteúdo de uma diretoria, identificando ficheiros e pastas.
 * 
 * @param path Caminho da diretoria a listar.
 */
void lista_diretorio(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char full_path[1024];

    dir = opendir(path);
    if (dir == NULL) {
        perror("Erro ao abrir diretoria");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Ignora "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Aqui construi o caminho completo
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &st) == -1) {
            perror("Erro ao obter informacao do ficheiro");
            continue;
        }

        printf("%s ", entry->d_name);

        if (S_ISREG(st.st_mode)) {
            printf("(ficheiro)\n");
        } else if (S_ISDIR(st.st_mode)) {
            printf("(diretoria)\n");
        } else {
            printf("(outro)\n");
        }
    }

    closedir(dir);
}
