#include<stdio.h>
#include<stdlib.h>
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

    FILE *fdlincol;
    fdlincol = fopen("Trabalhos.tsv", "r"); //PRECISA DEIXAR O "Trabalhos.tsv" COMO PARÂMETRO UNIVERSAL
    if (fdlincol == NULL){
    fprintf(stderr, "Erro ao abrir o entradas.txt\n");
    exit (-1);
    }
    int nlin, ncol;
    numLinColArquivo(fdlincol, &nlin, &ncol);
    fclose(fdlincol);
    
    FILE *fd;
    fd = fopen("Trabalhos.tsv", "r");
        if (fd == NULL){
        fprintf(stderr, "Erro ao abrir o entradas.txt\n");
        exit (-1);
    }
    tabela *docentes;

    docentes = alocaDados(nlin, ncol);
    pegaDados(docentes, fd);
    
    for (int m = 0; m < nlin; m++){
        for (int l = 0; l < ncol; l++){
            printf("%s\n", docentes -> dados[m][l]);
        }
    }

    destruir_tabela(docentes, nlin, ncol);
    fclose(fd);
    
    printf("%s\n%s\n%s", str_select, str_from, str_where);
}
