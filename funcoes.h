#ifndef __FUNCOES_H__
#define __FUNCOES_H__

typedef struct {
    char *nome_colunas;
    char ***dados;
} tabela;

void substring(char str[], char dest[], char str1[], char str2[]);

int *parametrosArquivo (char nome_do_arquivo[], int *nlin, int *ncol);

char **separaString (char str[]);

tabela *lerArquivo (char nome_do_arquivo[], int nlin, int ncol);

void imprimirResultado();

#endif