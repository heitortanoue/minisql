#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcoes.h"

int main(void) {
    char input[500];
    fgets(input, 500, stdin);
    int tem_where = 1;
    char str_select[150], str_from[100], str_where[200];
    substring(input, str_select, "select ", "from");
    if (substring(input, str_from, "from ", "where")) {
        substring(input, str_where, "where ", "\0");
    } else {
        substring(input, str_from, "from ", "\0");
        tem_where = 0;
    }

    int num_arquivos = 0;
    char **arr_nomes_arquivos;
    arr_nomes_arquivos = separaString(str_from, ", ", &num_arquivos);
    for (int i = 0; i < num_arquivos; i++) {
        int nlin, ncol;
        char arquivo_atual[strlen(arr_nomes_arquivos[i]) + 4];
        strcpy(arquivo_atual, arr_nomes_arquivos[i]);
        strcat(arquivo_atual, ".tsv");
        numLinColArquivo(arquivo_atual, &nlin, &ncol);
        FILE *fd;
        fd = fopen(arquivo_atual, "r");
        if (fd == NULL) {
            fprintf(stderr, "Erro ao abrir o %s.tsv\n", arquivo_atual);
            exit (-1);
        }
        tabela *tabela_arquivo;
        tabela_arquivo = alocaDados(nlin, ncol);
        pegaDados(tabela_arquivo, fd);
        
        for (int m = 0; m < nlin; m++){
            for (int l = 0; l < ncol; l++){
                printf("%s\n", tabela_arquivo -> dados[m][l]);
            }
        }
            destruir_tabela(tabela_arquivo, nlin, ncol);
            fclose(fd);  
    }

    // for (int i = 0; i < num_arquivos; i++) {
    //     destruir_tabela(tabela_arquivo, nlin, ncol);
    //     fclose(fd);
    // }
    for (int i = 0; i < num_arquivos; i++) {
        free(arr_nomes_arquivos[i]);
    }
    free(arr_nomes_arquivos);

}
