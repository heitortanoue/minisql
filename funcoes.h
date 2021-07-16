#ifndef __FUNCOES_H__
#define __FUNCOES_H__
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

typedef struct {
    char **nome_colunas;
    char ***dados;
} tabela;

void colocarColunasStruct (tabela *t, FILE *fd);

int substring(char str[], char dest[], char str1[], char str2[]);

int *parametrosArquivo (char nome_do_arquivo[], int *nlin, int *ncol);

char **separaString (char str[]);

tabela *lerArquivo (char nome_do_arquivo[], int nlin, int ncol);

void imprimirResultado();

#endif