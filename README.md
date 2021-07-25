# MiniSQL
> **Trabalho em C para ICC 01 / 2021**

Faça um programa que leia uma linha da entrada padrão, e a interprete como uma “consulta simples” a arquivos TSV. Um arquivo TSV é um arquivo texto, com valores separados por tabulações. A primeira linha tem o cabeçalho do arquivo.


### Exemplo 01:
    select Progs.Sigla, Progs.Nome from Progs where Progs.Nivel = “7”

Deve produzir como saída a sigla e o nome de todos os programas com Nível 7. Uma consulta tem três partes:

O select é uma lista de campos a serem impressos. Cada campo é formado pelo nome do arquivo, seguido de ponto, seguido do nome da coluna. As colunas são separadas por vírgula.

O from é a lista de arquivos que devem ser lidos. É uma lista de nomes de arquivos, separados por vírgula. A extensão “.tsv” deve ser assumida.

O where é uma lista de comparações. Esse campo é opcional. Cada comparação é do formato “Arquivo.campo = A”, onde “A” pode ser uma string, ou uma expressão “Arquivo.campo”. As comparações são separadas por “and”.


### Exemplo 02:
    select Docentes.Nome from Docentes where Docentes.Sexo = "MASCULINO"

Deve produzir a lista de docentes do sexo masculino


### Exemplo 03:
    select Progs.Programa, Progs.Nome from Progs

Deve produzir a lista de todos os programas, com os campos Programa e Nome.


### Exemplo 04:
    select Progs.Sigla, Docentes.Nome from Progs, Docentes where Progs.Programa = Docentes.CodigodoPPG

Deve produzir a lista com a sigla do programa e o nome do docente, sendo que os campos Programa e CodigodoPPG devem ser iguais


### Exemplo 05:
    select Progs.Sigla, Docentes.Nome, Trabalhos.Autor, Trabalho.Idioma, Docentes.Nacionalidade from Progs, Docentes, Trabalhos where Progs.Nivel = "6" and Progs.Programa =  Docentes.CodigodoPPG and Progs.Programa = Trabalhos.CodigodoPPG and Trabalhos.Orientador = Docentes.Nome

Deve produzir a lista de sigla do programa, com o nome do orientador (docente), o nome do autor do trabalho, idioma do trabalho, a nacionalidade do orientador (docente).
