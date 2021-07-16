#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int substring(char str[], char dest[], char str1[], char str2[]) {
    int i = 0;
    int ind1 = 0, ind2 = 0;
    while (str[i] != 0) {
        if (str[i] == str1[0] && ind1 == 0) {
            int e_igual = 1;
            for (unsigned int j = 0; j < strlen(str1); j++) {
                if (str[i] != str1[j]) {
                    e_igual = 0;
                    break;
                }
                i++;
            }
            if (e_igual) {
                ind1 = i;
            }
        }
        if (strcmp(str2, "\0") == 0) {
            ind2 = strlen(str) - 1;
        } else if (str[i] == str2[0] && ind2 == 0) {
            int tempind = i;
            int e_igual = 1;
            for (unsigned int j = 0; j < strlen(str2); j++) {
                if (str[i] != str2[j]) {
                    e_igual = 0;
                    break;
                }
                i++;
            }
            if (e_igual) {
                ind2 = tempind;
            }
        }
        i++;
    }

    if (ind1 != 0 && ind2 != 0) {
        int dest_counter = 0;
        for (int j = ind1; j < ind2; j++) {
            dest[dest_counter] = str[j];
            dest_counter++;
        }
        dest[dest_counter] = 0;
        return 1;
    } else {
        return 0;
    }
}

int contaOcorrenciasString (char *str, char *pedaco) {
    char copiastring[strlen(str)];
    strcpy(copiastring, str);
    char *token;
    token = strtok(str, pedaco);
    int ocorrencias = 1;
    while (token != NULL) {
        token = strtok(NULL, pedaco);
        ocorrencias++;
    }
    return ocorrencias;
}

// CONSERTAR STRTOK
char **separaString (char *str, char *espacador, int *size) {
    char *token = strtok(str, espacador);
    int tamanho_array = contaOcorrenciasString(str, espacador);
    char **array = malloc(sizeof (char *) * tamanho_array);
    for (unsigned int i = 0; i < tamanho_array; i++) {
        array[i] = malloc(sizeof(char) * 64); 
    }
    int i = 0;
    while (token != NULL) {
        strcpy(array[i], token);
        printf("[%d] %s foi copiado\n", i, array[i]);
        token = strtok(NULL, espacador);
        i++;
    }
    *size = tamanho_array;
    return array;
}