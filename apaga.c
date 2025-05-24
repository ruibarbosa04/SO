/**
 * @file apaga.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Apaga o ficheiro dito pelo utilizador
 * @version 0.1
 * @date 2025-05-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include "funcoes.h"

/**
 * @brief Apaga um ficheiro do sistema de ficheiros.
 * 
 * @param nome Nome (ou caminho) do ficheiro a remover.
 * @return int Retorna 0 se a operação for bem-sucedida, 1 em caso de erro.
 */
int apaga_ficheiro(const char *nome) {
    // Tenta remover o ficheiro indicado
    if (unlink(nome) == 0) {
        printf("Ficheiro '%s' apagado com sucesso.\n", nome);
        return 0;
    } else {
        // Se não conseguir, imprime a mensagem de erro
        perror("Erro ao apagar ficheiro");
        return 1;
    }
}
