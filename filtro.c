#include "filtro.h"
#include "nova_string.h"
#include "arquivo_tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna, int *index_tabela){
    char **strings = separaString(qual_coluna, ".");

    int index_selecionado;
    for (int i = 0; i < num_tabelas; i++) {
        if (strcmp(tabelas[i]->nome_arquivo, strings[0]) == 0) {
            index_selecionado = i;
            break;
        }
    }

    int ncol_filtro;
    for (int i = 0; i < tabelas[index_selecionado]->ncol; i++) {
        if (strcmp(tabelas[index_selecionado]->dados[0][i], strings[1]) == 0) { 
            ncol_filtro = i;
            break;
        } else {
        }
    }

    *index_tabela = index_selecionado;
    destruirArrayStrings(strings, 2);
    return ncol_filtro;
}

void FiltrarImprimir (tabela **tabelas, int num_tabelas, char **filtros, int num_filtros, char** colunas_selecionadas, int num_colunas) {
    int index_tabela;
    //0: index da tabela e 1: index da coluna selecionada
    int arr_index_colunas[num_colunas][2];
    for (int i = 0; i < num_colunas; i++) {
        arr_index_colunas[i][1] = indexColunaSelecionada(tabelas, num_tabelas, colunas_selecionadas[i], &index_tabela);
        arr_index_colunas[i][0] = index_tabela;
    }

    char ***filtros_separados;
    int tipo_filtro[num_filtros];
    if (num_filtros) {
        filtros_separados = malloc(sizeof(char **) * num_filtros);
        for (int i = 0; i < num_filtros; i++) {
            filtros_separados[i] = separaString(filtros[i], " =");
            // VERIFICA SE TEM ASPAS
            if (strchr(filtros_separados[i][1], '\"')) {
                tipo_filtro[i] = 1;
                substring(filtros_separados[i][1], filtros_separados[i][1], "\"", "\"");
            } else {
                tipo_filtro[i] = 0;
            }
        }
    }

    for (int linha = 1; linha < tabelas[0]->nlin - 1; linha++) {
        int linha_dentro_condicoes = 1;
        int arr_index_linha[num_tabelas];
        arr_index_linha[0] = linha;
        if (num_filtros) {
            for (int i = 0; i < num_filtros; i++) {
                int condicao = 1;
                if (tipo_filtro[i]) {
                    // COMPARAÇÃO VALORES
                    int ind_tabela;
                    int ind_coluna = indexColunaSelecionada(tabelas, num_tabelas, filtros_separados[i][0], &ind_tabela);
                    condicao = (!strcmp(tabelas[ind_tabela]->dados[linha][ind_coluna], filtros_separados[i][1]));
                    arr_index_linha[ind_tabela] = linha;
                    // if (condicao) {
                    //     printf("V: [%s == %s]\n", tabelas[ind_tabela]->dados[linha][ind_coluna], filtros_separados[i][1]);
                    // } else {
                    //     printf("V: [%s != %s]\n", tabelas[ind_tabela]->dados[linha][ind_coluna], filtros_separados[i][1]);
                    // }
                } else {
                    //COMPARAÇÃO CÉLULAS
                    int ind_tabela1, ind_tabela2;
                    int ind_coluna1 = indexColunaSelecionada(tabelas, num_tabelas, filtros_separados[i][0], &ind_tabela1);
                    int ind_coluna2 = indexColunaSelecionada(tabelas, num_tabelas, filtros_separados[i][1], &ind_tabela2);
                    int achou = 0;
                    for (int iterador = 0; iterador < tabelas[ind_tabela1]->nlin; iterador++) {
                        achou = (!strcmp(tabelas[ind_tabela2]->dados[linha][ind_coluna2], tabelas[ind_tabela1]->dados[iterador][ind_coluna1]));
                        if (achou) {
                            achou = 1;
                            arr_index_linha[ind_tabela2] = linha;
                            arr_index_linha[ind_tabela1] = iterador;
                            break;
                        }
                    }
                    condicao = achou;
                } 
                linha_dentro_condicoes = linha_dentro_condicoes && condicao;
            }
        }

        if (linha_dentro_condicoes) {
            for (int coluna = 0; coluna < num_colunas; coluna++) {
                int ind_tabela = arr_index_colunas[coluna][0];
                int ind_coluna = arr_index_colunas[coluna][1];
                int ind_linha = arr_index_linha[arr_index_colunas[coluna][0]];
                printf("%s", tabelas[ind_tabela]->dados[ind_linha][ind_coluna]);
                if (num_colunas > 1) {
                    printf("\t");
                }
            }
            if (linha < tabelas[0]->nlin - 2) {
                printf("\n");
            }
        }
    }

    if (num_filtros) {
        for (int i = 0; i < num_filtros; i++) {
            destruirArrayStrings(filtros_separados[i], 2);
        }
        free(filtros_separados);
    }
}
