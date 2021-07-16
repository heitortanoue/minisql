#ifndef __FUNCOES_H__
#define __FUNCOES_H__
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

typedef struct {
    char ***dados;
} tabela;

int substring(char str[], char dest[], char str1[], char str2[]);

int *parametrosArquivo (char nome_do_arquivo[], int *nlin, int *ncol);

char **separaString (char *str, char *espacador, int *size);

tabela *lerArquivos (char nome_do_arquivo[], int nlin, int ncol);

void imprimirResultado();

void numLinColArquivo (char *arquivo, int *numLin, int *numcol);

void destruir_tabela (tabela *tabela_utilizada, int nlin, int ncol);

tabela *alocaDados (int nlin, int ncol);

void pegaDados (tabela *tabela_alocada, FILE *fd);

int contaOcorrenciasString (char *str, char *pedaco);

#endif