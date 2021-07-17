#ifndef __ARQUIVOS_H__
#define __ARQUIVOS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"tabela.h"

void pegaDadosArquivo (tabela *tabela_alocada, FILE *fd);

void numLinColArquivo (char *arquivo, int *numLin, int *numcol);

#endif