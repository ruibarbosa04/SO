/**
 * @file interpretador.c
 * @author Rui Barbosa (a31515@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 22-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funcoes.h"
 
#define MAX_INPUT 50
#define MAX_ARGS 10

int interpretador(){
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

        while (1) {                                                                                 // while infinito 
            printf("%% ");                                                                          // printa "%" na consola
            fflush(stdout);                                                                         // forca a escrita do print em cima

            if (fgets(input, sizeof(input), stdin) == NULL) {                                       // le a linha do input
            break;
            }

            input[strcspn(input, "\n")] = '\0';                                                     // sempre que input carregar no enter ele coloca /0 para inidicar final da instrucao 

            if (strcmp(input, "termina") == 0) {                                                     // se o utilizador escrever "termina" ele termmina o while , "termina" comando para sair 
            break;
            }

            if(strcmp(input, "apaga")==0){
                
            }

            int i = 0;
            char *token = strtok(input, " ");
            while (token != NULL && i < MAX_ARGS - 1) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            if (args[0] == NULL) {
                continue;  
            }   

            // Verificar se é o comando "apaga" e se tem argumento a frente 
            if (strcmp(args[0], "apaga") == 0) {
                if (args[1] == NULL) {
                    printf("Erro: tem de indicar o nome do ficheiro a apagar.\n");
                continue;
                }          
                int resultado=apaga_ficheiro(args[1]);
                printf("Terminou comando apaga com codigo %d\n", resultado);  
            }
            // verifica se é o comando "lista" 
            else if (strcmp(args[0], "lista") == 0) {
            if (args[1] == NULL) {
                printf("Erro: tem de indicar o caminho da diretoria a listar.\n");
                continue;
            }

            lista_diretorio(args[1]);
            printf("Terminou comando lista com código 0\n");
            }   
            else if (strcmp(args[0], "informa") == 0) {
                if (args[1] == NULL) {
                    printf("Erro: tem de indicar o nome do ficheiro.\n");
                    continue;
                }
                mostra_info(args[1]);
                printf("Terminou comando informa com código 0\n");
            }else{
                printf("Comando desconhecido: %s\n", args[0]); 
            }
        }   
    return 0; 
}

int main() {
    return interpretador();  // chama o interpretador
}