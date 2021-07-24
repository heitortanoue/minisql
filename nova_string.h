#ifndef __NOVA_STRING_H__
#define __NOVA_STRING_H__

int substring (char str[], char dest[], const char str1[], const char str2[]);

int contaOcorrenciasString (char *str, const char *pedaco);

char **separaString (char *str_inp, const char *espacador);

void destruirArrayStrings (char **arr_str, int num_strings);

#endif