#include<stdio.h>
#include<stdlib.h>
#include"funcoes.h"

int main(void) {
    char input[500];
    fgets(input, 500, stdin);
    int tem_where = 1;
    char str_select[150], str_from[100], str_where[200];
    substring(input, str_select, "select ", "from");
    if (substring(input, str_from, "from ", "where")) {
        substring(input, str_where, "where ", "\0");
    } else {
        substring(input, str_from, "from ", "\0");
        tem_where = 0;
    }

    printf("%s\n%s\n%s", str_select, str_from, str_where);
}
