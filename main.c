#include"arquivo_tabela.h"
#include"nova_string.h"
#include"filtro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int main(void) {
    // ENTRADA STRING E DIVISÃO DAS PARTES SELECT, FROM E WHERE
    char input[1500];
    fgets(input, 1024, stdin);
    int tem_where = 1;
    char str_select[500], str_from[500], str_where[500];
    substring(input, str_select, "select ", "from");
    if (substring(input, str_from, "from ", "where")) {
        substring(input, str_where, "where ", "\0");
    } else {
        substring(input, str_from, "from ", "\0");
        tem_where = 0;
    }

    // CRIAÇÃO DE UM ARRAY COM NOMES DOS ARQUIVOS DO FROM
    int num_arquivos = contaOcorrenciasString(str_from, ",");
    char **nomes_arquivos;
    nomes_arquivos = separaString(str_from, ",");

    // CRIAÇÃO DE UMA TABELA PARA CADA ARQUIVO COM SEUS DADOS
    tabela *tabelas[num_arquivos];
    for (int i = 0; i < num_arquivos; i++) {
        tabelas[i] = abreArquivoCriaTabela(nomes_arquivos[i]);
    }

    // for (int i = 0; i < num_arquivos; i++) {
    //     printf("[%s (%d x %d)]\n", tabelas[i]->nome_arquivo, tabelas[i]->nlin, tabelas[i]->ncol);
    // }

    // CRIAÇÃO DE UM ARRAY COM NOMES DAS COLUNAS SELECIONADAS NO SELECT
    int num_colunas_selecionadas = contaOcorrenciasString(str_select, ",");
    char **colunas_selecionadas;
    colunas_selecionadas = separaString(str_select, ",");

    // for (int i = 0; i < num_colunas_selecionadas; i++) {
    //     int alo;
    //     printf("[%s (%d)]\n", colunas_selecionadas[i], indexColunaSelecionada(tabelas, num_arquivos, colunas_selecionadas[i], &alo));
    // }


    if (tem_where) {
        int num_filtros = contaOcorrenciasString(str_where, " and");
        char **filtros = separaString(str_where, " and");
        FiltrarImprimir(tabelas, num_arquivos, filtros, num_filtros, colunas_selecionadas, num_colunas_selecionadas);
        destruirArrayStrings(filtros, num_filtros);
    } else {
        imprimirTabelaResultado(tabelas, colunas_selecionadas, num_arquivos, num_colunas_selecionadas);
    }

    destruirArrayStrings(nomes_arquivos, num_arquivos);
    destruirArrayStrings(colunas_selecionadas, num_colunas_selecionadas);
    for (int i = 0; i < num_arquivos; i++) {
        fclose(tabelas[i]->arquivo);
        destruirTabela(tabelas[i], tabelas[i]->nlin, tabelas[i]->ncol);       
    }
}