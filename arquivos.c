#include"arquivos.h"

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
            tabela_alocada -> dados[i][j][k] = '\0';
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