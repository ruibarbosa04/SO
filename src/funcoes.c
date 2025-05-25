#include <fcntl.h>      // open
#include <unistd.h>     // read, write, close, STDERR_FILENO
#include <stdio.h>      // dprintf, fprintf, printf
#include <stdlib.h>     // exit (caso use no futuro)
#include <string.h>     // strcmp, strerror
#include <errno.h>      // errno
#include <sys/stat.h>   // stat, S_ISREG, etc
#include <pwd.h>        // getpwuid
#include <time.h>       // time, localtime, strftime
#include <dirent.h>     // DIR, opendir, readdir, closedir
#include "funcoes.h"    // protótipos das funções, se necessário

#define TAMANHO_BUFFER 1024

/**
 * @brief Apresenta todo o conteúdo que o ficheiro contém
 * 
 * @param nome_ficheiro Nome do ficheiro a obter o conteúdo.
 */
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

/**
 * @brief Cria um novo ficheiro copia, cujo o conteúdo é uma copia de todo o ficheiro passado no parâmetro da consola
 * 
 * @param nome_ficheiro Nome do ficheiro a copiar o conteúdo
 */
void copia_ficheiro(const char *nome_ficheiro) {
    int fd_in = open(nome_ficheiro, O_RDONLY);
    if (fd_in < 0) {
        dprintf(2, "Erro: ficheiro '%s' não existe ou não pode ser aberto\n", nome_ficheiro);
        return;
    }

    char nome_copia[1024];
    snprintf(nome_copia, sizeof(nome_copia), "%s.copia", nome_ficheiro);

    int fd_out = open(nome_copia, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        dprintf(2, "Erro: não foi possível criar '%s'\n", nome_copia);
        close(fd_in);
        return;
    }

    char buffer[TAMANHO_BUFFER];
    ssize_t bytes_lidos;
    while ((bytes_lidos = read(fd_in, buffer, TAMANHO_BUFFER)) > 0) {
        ssize_t bytes_escritos = write(fd_out, buffer, bytes_lidos);
        if (bytes_escritos != bytes_lidos) {
            dprintf(2, "Erro ao escrever em '%s'\n", nome_copia);
            break;
        }
    }
    if (bytes_lidos < 0)
        dprintf(2, "Erro ao ler o ficheiro '%s'\n", nome_ficheiro);

    close(fd_in);
    close(fd_out);
}

/**
 * @brief Acrescenta o conteúdo do ficheiro de origem no ficheiro de destino
 * 
 * @param origem ficheiro de origem do conteúdo 
 * @param destino ficheiro de destino do conteúdo
 */
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

/**
 * @brief Conta o número de linhas existens num ficheiro
 * 
 * @param nome_ficheiro Nome do ficheiro a contar as linhas 
 */
void conta(const char* nome_ficheiro) {
    int fd = open(nome_ficheiro, O_RDONLY);  // Tenta abrir o ficheiro em modo leitura

    if (fd == -1) {
        dprintf(STDERR_FILENO, "Erro: Não foi possível abrir o ficheiro '%s'\n", nome_ficheiro);
        return;
    }

    char buffer[TAMANHO_BUFFER];
    char linhas = 1;
    ssize_t bytes_lidos;

    // Lê o ficheiro e escreve no stdout
    while ((bytes_lidos = read(fd, buffer, TAMANHO_BUFFER)) > 0) {
       for(ssize_t i = 0; i < bytes_lidos; i++){
        if(buffer[i] == '\n'){
             linhas++;
        }
      }
    }

    if(bytes_lidos == -1){
        dprintf(STDERR_FILENO, "Erro: Ocorreu um erro durante a leitura do ficheiro '%s'\n", nome_ficheiro);
    } else {
        dprintf(STDOUT_FILENO, "Número de linhas: %d\n", linhas);
    }
    close(fd);
}

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
        fprintf(stderr, "Erro ao apagar ficheiro '%s': %s\n", nome, strerror(errno));
        return 1;
    }
}

/**
 * @brief Mostra informações detalhadas sobre um ficheiro.
 * 
 * @param ficheiro Nome (ou caminho) do ficheiro a analisar.
 */
void mostra_info(const char *ficheiro) {
    struct stat st;

    if (stat(ficheiro, &st) == -1) {
        fprintf(stderr, "Erro ao obter informação do ficheiro '%s': %s\n", ficheiro, strerror(errno));
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
        fprintf(stderr, "Erro ao abrir diretoria '%s': %s\n", path, strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Ignora "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Aqui construi o caminho completo
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &st) == -1) {
            fprintf(stderr, "Erro ao obter informação do ficheiro '%s': %s\n", full_path, strerror(errno));
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


