#include"arquivo_tabela.h"
#include"filtro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMCARACT (256)

tabela *alocaDadosTabela (int nlin, int ncol) {
    tabela *dados_alocados = malloc (sizeof(tabela) * 1);
       if (dados_alocados == NULL){
            exit(-1);
        }
    dados_alocados -> dados = malloc (sizeof(char **) * nlin);
       if (dados_alocados -> dados == NULL){
            exit(-1);
        }
    for (int i = 0; i < nlin; i++){
        dados_alocados -> dados[i] = malloc (sizeof(char *) * ncol);
           if (dados_alocados -> dados[i] == NULL){
                exit(-1);
            }
        for (int j = 0; j < ncol; j++){
            dados_alocados -> dados[i][j] = malloc(sizeof(char) *  NUMCARACT);
        }
    }
    dados_alocados->nlin = nlin;
    dados_alocados->ncol = ncol;
    return dados_alocados;
}


void destruirTabela (tabela *tabela_utilizada, int nlin, int ncol){
    for (int i = 0; i < nlin; i++){
        for(int j = 0; j < ncol; j++){
            free(tabela_utilizada -> dados[i][j]);
        }
        free(tabela_utilizada -> dados[i]);
    }
    free(tabela_utilizada -> dados);
    free(tabela_utilizada);
}


tabela *abreArquivoCriaTabela (char *nome_arquivo) {
        int nlin, ncol;
        char arquivo_atual[strlen(nome_arquivo) + 4];
        strcpy(arquivo_atual, nome_arquivo);
        strcat(arquivo_atual, ".tsv");
        numLinColArquivo(arquivo_atual, &nlin, &ncol);
        FILE *fd;
        fd = fopen(arquivo_atual, "r");
        if (fd == NULL) {
            fprintf(stderr, "Erro ao abrir o %s\n", arquivo_atual);
            exit (-1);
        }
        tabela *tabela_arquivo;
        tabela_arquivo = alocaDadosTabela(nlin, ncol);
        pegaDadosArquivo(tabela_arquivo, fd);
        tabela_arquivo->arquivo = fd;
        strcpy(tabela_arquivo->nome_arquivo, nome_arquivo);
        return tabela_arquivo;
}


void pegaDadosArquivo (tabela *tabela_alocada, FILE *fd){
    int i = 0;
    int j = 0;
    int k = 0;
    int fimlinha = 0;
    while(!feof(fd)){
        while(!fimlinha && !feof(fd)){
            do {
                tabela_alocada -> dados[i][j][k] = fgetc(fd);
                k++;
            } while(tabela_alocada -> dados[i][j][k - 1] != '\t' && tabela_alocada -> dados[i][j][k-1] != '\n' && !feof(fd));
            if (tabela_alocada -> dados[i][j][k - 1] == '\n'){
                fimlinha = 1;
            }
            tabela_alocada -> dados[i][j][k - 1] = '\0';
            k = 0;
            j++;
        }
        j = 0;
        i++;
        fimlinha = 0;
    }
}


void numLinColArquivo (char *arquivo, int *numLin, int *numcol){
    FILE *fdlc;
    fdlc = fopen(arquivo, "r");
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
    fclose(fdlc);
}
// select Progs.Sigla, Docentes.Nome from Progs, Docentes
void imprimirTabelaResultado (tabela **tabelas, char *colunas_selecionadas[], int num_arquivos, int num_colunas) {
    int menor_index_tabela = 0, index_tabela;
    int arr_index_colunas[num_colunas][2];
    for (int i = 0; i < num_colunas; i++) {
        arr_index_colunas[i][1] = indexColunaSelecionada(tabelas, num_arquivos, colunas_selecionadas[i], &index_tabela);
        arr_index_colunas[i][0] = index_tabela;
        if (tabelas[index_tabela]->nlin < tabelas[menor_index_tabela]->nlin) {
            menor_index_tabela = index_tabela;
        }
    }
    int numero_linhas = tabelas[menor_index_tabela]->nlin;
    for (int m = 1; m < numero_linhas; m++) {  
        for (int l = 0; l < num_colunas; l++) {
            printf("%s\t", tabelas[arr_index_colunas[l][0]]->dados[m][arr_index_colunas[l][1]]);
        }
        if (m < numero_linhas - 2) {
            printf("\n");
        }
    }
}

