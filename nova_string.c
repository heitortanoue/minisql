#include"nova_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_CARACTERES (256)
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int substring (char str[], char dest[], char str1[], char str2[]) {
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
            if (j == ind2 - 1 && str[j] == ' ') {
                break;
            }
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
    int i, j;
    int ocorrencias = 1;
    int l1 = strlen(str);
    int l2 = strlen(pedaco);
    for (i = 0; i < l1 - l2 + 1; i++) {
        if (strstr(str + i, pedaco) == str + i) {
        ocorrencias++;
        i = i + l2 - 1;
        }
    }
    return ocorrencias;
}

char **separaString (char *str_inp, char *espacador) {
    int num_strings = contaOcorrenciasString(str_inp, espacador);
    char string_formatada[strlen(str_inp)];
    int g = 0, h = 0;
    while(str_inp[g] != '\0'){
        int achou_palavra = 1;
        for (unsigned int count = 0; count < strlen(espacador); count++) {
            achou_palavra = achou_palavra && str_inp[g + count] == espacador[count];
        }
        if (achou_palavra){
            string_formatada[h] = '&';
            g += strlen(espacador);
        } else {
            string_formatada[h] = str_inp[g];
        }
        g++;
        h++;
    }
    string_formatada[h] = '\0';
    
    char **arr_dest = malloc(sizeof(char *) * num_strings);
    for (int i = 0; i < num_strings; i++) {
        arr_dest[i] = malloc(sizeof(char) * NUM_CARACTERES);
    }

    char *pont_str;
    pont_str = strtok(string_formatada, "&");
    int i = 0;
    while (pont_str != NULL){
        strcpy(arr_dest[i], pont_str);
        int c = 0;
        i++;
        pont_str = strtok(NULL, "&");   
    }
    return arr_dest;
}

void destruirArrayStrings (char **arr_str, int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        free(arr_str[i]);
    }
    free(arr_str);
}