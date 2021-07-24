#ifndef __FILTRO_H__
#define __FILTRO_H__
#include "arquivo_tabela.h"

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna, int *index_tabela);

void FiltrarImprimir (tabela **tabelas, int num_tabelas, char **filtros, int num_filtros, char** colunas_selecionadas, int num_colunas);

#endif