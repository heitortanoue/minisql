#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "funcoes.h"
#define NUMCARACT (256)

tabela *alocaDados (int nlin, int ncol) {
    tabela *dados_alocados = malloc (sizeof(tabela) * 1);
       if (dados_alocados == NULL){
            printf("erro 1\n");
            exit(-1);
        }
    dados_alocados -> dados = malloc (sizeof(char **) * nlin);
       if (dados_alocados -> dados == NULL){
            printf("erro 2\n");
            exit(-1);
        }
    for (int i = 0; i < nlin; i++){
        dados_alocados -> dados[i] = malloc (sizeof(char *) * ncol);
           if (dados_alocados -> dados[i] == NULL){
                printf("erro 3 na linha %d\n", i);
                exit(-1);
            }
        for (int j = 0; j < ncol; j++){
            dados_alocados -> dados[i][j] = malloc(sizeof(char) *  NUMCARACT);
        }
    }

    return dados_alocados;
}

void destruir_tabela (tabela *tabela_utilizada, int nlin, int ncol){
    for (int i = 0; i < nlin; i++){
        for(int j = 0; j < ncol; j++){
            free(tabela_utilizada -> dados[i][j]);
        }
        free(tabela_utilizada -> dados[i]);
    }
    free(tabela_utilizada -> dados);
    free(tabela_utilizada);
}


/*void colocarColunasStruct (tabela *t, FILE *fd) {
    char string_primeira_linha[200];
    fgets(string_primeira_linha, 200, fd);
    char* tok;
    const char s[4] = " ";
    tok = strtok(string_primeira_linha, s);
    printf("%s ", tok);
    int i = 0;
    while (tok != 0) {
        //t->nome_colunas[i] = tok;
        printf("%s ", tok);
        tok = strtok(0, s);
        i++;
    }
}*/

void pegaDados (tabela *tabela_alocada, FILE *fd){
    int i = 0;
    int j = 0;
    int k = 0;
    int fimlinha = 0;
    //colocarColunasStruct(tabela_alocada, fd);
    while(!feof(fd)){
        while(!fimlinha && !feof(fd)){
            do{
                tabela_alocada -> dados[i][j][k] = fgetc(fd);
                k++;
            } while(tabela_alocada -> dados[i][j][k - 1] != '\t' && tabela_alocada -> dados[i][j][k-1] != '\n' && !feof(fd));
            if(tabela_alocada -> dados[i][j][k - 1] == '\n'){
                fimlinha = 1;
            }
            tabela_alocada -> dados[i][j][k] = '\0';
            k = 0;
            j++;
        }
        j = 0;
        i++;
        fimlinha = 0;
    }
}

void numLinColArquivo (FILE *fdlc, int *numLin, int *numcol){
    char c;
    int lin = 0;
    int col = 0;
    int passou = 0;
    while(!feof(fdlc)){
        c = fgetc(fdlc);
        if(!passou && (c == '\t' || c == '\n')){
            col++;
        }

        if(c == '\n'){
            lin++;
            passou = 1;
        }
    }
    
    *numLin = lin + 1;
    *numcol = col;
}

int main (void){
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
}
