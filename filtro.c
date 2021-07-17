#include"filtro.h"
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char qual_coluna[]){
    int tamanho_max = strlen(qual_coluna);
    char str_depois_corte[tamanho_max];
    char str_antes_corte[tamanho_max];
    int j = 0, k = 0;
    int passou = 0;
    PASSOUAQUI
    for (int i = 0; i < tamanho_max; i++){
        if(qual_coluna[i] == '.'){
            passou = 1;
        }
        if (passou){
            str_depois_corte[j] = qual_coluna[i];
            j++;
        } else {
            str_antes_corte[k] = qual_coluna[i];
            k++;  
        }
    }
    PASSOUAQUI
    str_antes_corte[k] = 0;

    int index_selecionado;
    for (int i = 0; i < num_tabelas; i++) {
        PASSOUAQUI
        if (!strcmp(tabelas[i]->nome_arquivo, str_antes_corte)) {
            index_selecionado = i;
        }
    }
    PASSOUAQUI
    tamanho_max = strlen(str_depois_corte);
    int ncol_filtro = 0;
    int achou = 0;
    while(!achou){
        for(int l = 0; l < tamanho_max; l++){
            if (tabelas[index_selecionado] -> dados[0][ncol_filtro][l] != str_depois_corte[l]){
                ncol_filtro++;
                break;
            } else if (str_depois_corte[l + 1] == '\0'){
                achou = 1;
            }
        }
    }
    PASSOUAQUI
    return ncol_filtro;
}