#ifndef __FUNCOES_H__
#define __FUNCOES_H__

typedef struct {
    char *nome_colunas;
    char ***dados;
} tabela;

int *parametrosArquivo (char nome_do_arquivo[], int *nlin, int *ncol);

char **parametrosTerminal ();

char **separaString (char str[]);

tabela *lerArquivo (char nome_do_arquivo[], int nlin, int ncol);

void imprimirResultado();

#endif