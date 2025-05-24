/**
 * @file informa.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

/**
 * @brief Mostra informações detalhadas sobre um ficheiro.
 * 
 * @param ficheiro Nome (ou caminho) do ficheiro a analisar.
 */
void mostra_info(const char *ficheiro) {
    struct stat st;

    if (stat(ficheiro, &st) == -1) {
        perror("Erro ao obter informação do ficheiro");
        return;
    }

    // Tipo de ficheiro
    printf("Tipo de ficheiro: ");
    if (S_ISREG(st.st_mode)) {
        printf("Ficheiro normal\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("Diretoria\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("Link simbólico\n");
    } else {
        printf("Outro tipo\n");
    }

    // Número do i-node
    printf("i-node: %lu\n", st.st_ino);

    // Nome do utilizador (dono)
    struct passwd *pw = getpwuid(st.st_uid);
    if (pw != NULL) {
        printf("Dono: %s\n", pw->pw_name);
    } else {
        printf("Dono (UID): %d\n", st.st_uid);
    }

    // Datas
    char buffer[100];
    struct tm *tm_info;

    tm_info = localtime(&st.st_atime);  // Último acesso
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Último acesso: %s\n", buffer);

    tm_info = localtime(&st.st_mtime);  // Última modificação
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Última modificação: %s\n", buffer);

    tm_info = localtime(&st.st_ctime);  // Última alteração de metadados
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Última alteração de metadados: %s\n", buffer);
}
