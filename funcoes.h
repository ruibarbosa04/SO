/**
 * @file funcoes.h
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>

#ifndef FUNCOES_H
#define FUNCOES_H


/**
 * @brief Apaga um ficheiro do sistema de ficheiros.
 * 
 * @param nome Nome (ou caminho) do ficheiro a remover.
 * @return int 0 se for removido com sucesso, 1 caso contrário.
 */
int apaga_ficheiro(const char *nome);

/**
 * @brief Mostra informações detalhadas sobre um ficheiro.
 * 
 * Inclui tipo de ficheiro, número do i-node, nome do utilizador dono
 * e datas de acesso, modificação e alteração.
 * 
 * @param ficheiro Nome (ou caminho) do ficheiro a analisar.
 */
void mostra_info(const char *ficheiro);

/**
 * @brief Lista o conteúdo de uma diretoria.
 * 
 * Apresenta os nomes dos ficheiros e subpastas, indicando
 * se cada entrada é um ficheiro, diretoria ou outro tipo.
 * 
 * @param path Caminho da diretoria a listar. Se for NULL ou ".", usa a diretoria atual.
 */
void lista_diretorio(const char *path);


#endif
