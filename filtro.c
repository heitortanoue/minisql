#include"filtro.h"
#include"nova_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna, int *index_tabela) {
    // PEGA UMA STRING DO TIPO "Docentes.Nome" E PROCURA EM QUAL TABELA E EM QUAL COLUNA ESTÁ A INFORMAÇÃO
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

void FiltrarImprimir (tabela **tabelas, int num_tabelas, char **filtros, int num_filtros, char** colunas_selecionadas, int num_colunas) {
    // PEGA OS FILTROS DISPONIVEIS, OS SEPARA, E OS COMPARA COM AS TABELAS, IMPRIME O RESULTADO
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

    int linhas_total = tabelas[0]->nlin - 1;
    for (int i = 0; i < num_tabelas; i++) {
        if (tabelas[i]->nlin - 1 > linhas_total) {
            linhas_total = tabelas[i]->nlin - 1;
        }
    }

    for (int linha = 1; linha < linhas_total; linha++) {
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
                    if (strcmp(tabelas[ind_tabela]->dados[arr_index_linha[ind_tabela]][ind_coluna], filtros_separados[i][1])) {
                        linha_dentro_condicoes = 0;
                        break;
                    }
                    arr_index_linha[ind_tabela] = linha;
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
            if (linha < linhas_total - 1) {
                printf("\n");
            }
        }
    }

    if (num_filtros) {
        liberarMallocsTam3 (filtros_separados, num_filtros, 2);
    }
}