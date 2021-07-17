#ifndef __TABELA_H__
#define __TABELA_H__
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    char ***dados;
} tabela;

void destruirTabela (tabela *tabela_utilizada, int nlin, int ncol);

tabela *alocaDadosTabela (int nlin, int ncol);

#endif