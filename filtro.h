#ifndef __FILTRO_H__
#define __FILTRO_H__
#include"arquivo_tabela.h"
#include "nova_string.h"

int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna, int *index_tabela);
typedef struct {
    int tipo; // 0-CARACT 1-COMPARA
    int ntabela;
    //int local;
    int local_caract;
    char caracteristica[64];
    int ntabela1;
    int ntabela2;
    //int local[2];
    int local_compara[2]; 
} filtro;
void defineFiltros (tabela **tabelas, char where[]); //filtro **
#endif