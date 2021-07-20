#include"filtro.h"
#include"nova_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna, int *index_tabela){
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

    *index_tabela = index_selecionado;
    return ncol_filtro;
}

void separarFiltros (tabela **tabelas, int num_tabelas, char **filtros, int num_filtros) {
    char ***filtros_separados = malloc(sizeof(char ***) * 1);
    for (int i = 0; i < num_filtros; i++) {
        filtros_separados[i] = separaString(filtros[i], " =");
    }

    for (int i = 0; i < num_filtros; i++) {
        if (strchr(filtros_separados[i][1], '\"')) {
            // COMPARAÇÃO VALORES
            substring(filtros_separados[i][1], filtros_separados[i][1], "\"", "\"");
            printf("]\n[C. VALORES: %s e %s]\n", filtros_separados[i][0], filtros_separados[i][1]);
        } else {
            // COMPARAÇÃO CÉLULAS
            int ind1, ind2;
            indexColunaSelecionada(tabelas, num_tabelas, filtros_separados[i][0], &ind1);
            indexColunaSelecionada(tabelas, num_tabelas, filtros_separados[i][1], &ind2);
            printf("[C. CELULAS: %s(%d) e %s(%d)]\n", filtros_separados[i][0], ind1, filtros_separados[i][1], ind2);
        }
    }

    for (int i = 0; i < num_filtros; i++) {
        destruirArrayStrings(filtros_separados[i], 2);
    }
    free(filtros_separados);
}