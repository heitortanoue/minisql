#include"tabela.h"
#define NUMCARACT (256)

tabela *alocaDadosTabela (int nlin, int ncol) {
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
