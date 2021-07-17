#include"filtro.h"
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna){
    char str_depois_corte[20];
    char str_antes_corte[15];
    int j = 0, k = 0;
    int passou = 0;
    int count = 0;
    while (qual_coluna[count]) {
        if (passou){
            str_depois_corte[j] = qual_coluna[count];
            j++;
        } else {
            str_antes_corte[k] = qual_coluna[count];
            k++;  
        }
        if(qual_coluna[count] == '.'){
            passou = 1;
        }
        count++;
    }
    str_depois_corte[j] = 0;
    str_antes_corte[k - 1] = 0;

    int index_selecionado;
    for (int i = 0; i < num_tabelas; i++) {
        if (!strcmp(tabelas[i]->nome_arquivo, str_antes_corte)) {
            index_selecionado = i;
            break;
        }
    }

    int ncol_filtro;
    for (int i = 0; i < tabelas[index_selecionado]->ncol; i++) {
        if (!strcmp(tabelas[index_selecionado] -> dados[0][i], str_depois_corte)) { 
            ncol_filtro = i;
            break;
        }
    }

    return ncol_filtro;
}