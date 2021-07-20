#include"filtro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);
int indexColunaSelecionada(tabela **tabelas, int num_tabelas, char *qual_coluna, int *index_tabela){
    char str_depois_corte[20];
    char str_antes_corte[15];
    int j = 0, k = 0;
    int passou = 0;
    int count = 0;
    while (qual_coluna[count]) {
        if (passou){
            str_depois_corte[j] = qual_coluna[count];
            j++;
        } else {
            str_antes_corte[k] = qual_coluna[count];
            k++;  
        }
        if(qual_coluna[count] == '.'){
            passou = 1;
        }
        count++;
    }
    str_depois_corte[j] = 0;
    str_antes_corte[k - 1] = 0;

    int index_selecionado;
    for (int i = 0; i < num_tabelas; i++) {
        if (!strcmp(tabelas[i]->nome_arquivo, str_antes_corte)) {
            index_selecionado = i;
            break;
        }
    }

    int ncol_filtro;
    for (int i = 0; i < tabelas[index_selecionado]->ncol; i++) {
        if (!strcmp(tabelas[index_selecionado] -> dados[0][i], str_depois_corte)) { 
            ncol_filtro = i;
            break;
        }
    }

    *index_tabela = index_selecionado;
    return ncol_filtro;
}


filtro **defineFiltros (tabela **tabelas, char where[]){
    int qnt_filtros = contaOcorrenciasString(where, "and");
    char where_sem_and[strlen(where)];
    int g = 0;
    int h = 0;
    while(where[g] != '\0'){
        if (where[g] == 'a' && where[g + 1] == 'n' && where[g + 2] == 'd'){
            where_sem_and[h] = '/';
            g += 4;
            h++;
        } else {
            where_sem_and[h] = where[g];
            g++;
            h++;
        }
    }
    where_sem_and[h] = '\0';
    printf("%s\n", where_sem_and);
    
    char filtros_separados[qnt_filtros][64];
    char *pont_str;
    pont_str = strtok(where_sem_and, "/");
    int i = 0;
    while (pont_str != NULL){
        strcpy(filtros_separados[i], pont_str);
        printf("%s\n", filtros_separados[i]);
        i++;
        pont_str = strtok(NULL, "/");   
    }
    filtro **todos_filtros; //##DAR MALLOC
    for (int j = 0; j < qnt_filtros; j++){
        int k = 0;
        int passou_igual = 0;
        while (filtros_separados[j][k] != '\0'){
            if (filtros_separados[j][k] == '='){
                passou_igual = 1;
                k += 2;
            }
            if (passou_igual && filtros_separados[j][k] == '"'){
                k++;
                int l = 0;
                while(filtros_separados[j][k] != '"'){
                    todos_filtros[j]->tipo = 0;
                    todos_filtros[j]->ntabela = j; // ### TAMBÉM NÃO SEI
                    todos_filtros[j]->local_caract = 0; // ### COMO FAZ PARA FAZER ISSO? NÃO SEI
                    todos_filtros[j]->caracteristica[l] = filtros_separados[j][k];
                    l++;
                    k++;
                }
            } else if(passou_igual){
                int m = 0;
                todos_filtros[j]->tipo = 1;
                /*while(){

                }*/
            }
            k++;
        }
    }
    return todos_filtros;
} //Progs.Nivel = "6" and Progs.Programa = Docentes.CodigodoPPG and Progs.Programa = Trabalhos.CodigodoPPG and Trabalhos.Orientador = Docentes.Nome