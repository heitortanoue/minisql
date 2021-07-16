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