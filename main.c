#include"arquivo_tabela.h"
#include"nova_string.h"
#include"filtro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int main(void) {
    // ENTRADA STRING E DIVISÃO DAS PARTES SELECT, FROM E WHERE
    char input[1024];
    fgets(input, 1024, stdin);
    int tem_where = 1;
    char str_select[384], str_from[128], str_where[512];
    substring(input, str_select, "select ", "from");
    if (substring(input, str_from, "from ", "where")) {
        substring(input, str_where, "where ", "\0");
    } else {
        substring(input, str_from, "from ", "\0");
        tem_where = 0;
    }

    // CRIAÇÃO DE UM ARRAY COM NOMES DOS ARQUIVOS DO FROM
    int num_arquivos = contaOcorrenciasString(str_from, ", ");
    char *nomes_arquivos[num_arquivos];
    char *tok;
    tok = strtok(str_from, ", ");
    int count = 0;
    while (tok != 0) {
        nomes_arquivos[count] = tok;
        tok = strtok(0, ", ");
        count++;
    }

    // CRIAÇÃO DE UMA TABELA PARA CADA ARQUIVO COM SEUS DADOS
    tabela *tabelas[num_arquivos];
    for (int i = 0; i < num_arquivos; i++) {
        tabelas[i] = abreArquivoCriaTabela(nomes_arquivos[i]);
    }

    // for (int i = 0; i < num_arquivos; i++) {
    //     printf("[%s (%d x %d)]\n", tabelas[i]->nome_arquivo, tabelas[i]->nlin, tabelas[i]->ncol);
    // }
    // CRIAÇÃO DE UM ARRAY COM NOMES DAS COLUNAS SELECIONADAS NO SELECT
    
    int num_colunas_selecionadas = contaOcorrenciasString(str_select, ", ");
    char *colunas_selecionadas[num_colunas_selecionadas];
    char *tok1;
    tok1 = strtok(str_select, ", ");
    int count1 = 0;
    while (tok1 != 0) {
        colunas_selecionadas[count1] = tok1;
        tok1 = strtok(0, ", ");
        count1++;
    }
    // for (int i = 0; i < num_colunas_selecionadas; i++) {
    //     int alo;
    //     printf("[%s (%d)]\n", colunas_selecionadas[i], indexColunaSelecionada(tabelas, num_arquivos, colunas_selecionadas[i], &alo));
    // }

    imprimirTabelaResultado(tabelas, colunas_selecionadas, num_arquivos, num_colunas_selecionadas);
    
    defineFiltros (tabelas, str_where);
    for (int i = 0; i < num_arquivos; i++) {
        fclose(tabelas[i]->arquivo);
        destruirTabela(tabelas[i], tabelas[i]->nlin, tabelas[i]->ncol);       
    }
}