#ifndef __NOVA_STRING_H__
#define __NOVA_STRING_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int substring (char str[], char dest[], char str1[], char str2[]);

int contaOcorrenciasString (char *str, char *pedaco);

char **separaString (char *str_inp, char *espacador);

#endif