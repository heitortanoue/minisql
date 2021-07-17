all : main.o arquivos.o tabela.o nova_string.o
	gcc -o prog.exe tabela.o arquivos.o nova_string.o main.o arquivos.h tabela.h nova_string.h

run :
	./prog.exe

main.o : main.c
	gcc -o main.o -c main.c

arquivos.o : arquivos.c arquivos.h
	gcc -o arquivos.o -c arquivos.c

tabela.o : tabela.c tabela.h
	gcc -o tabela.o -c tabela.c

nova_string.o : nova_string.c nova_string.h
	gcc -o nova_string.o -c nova_string.c

clean :
	-del -f *.exe *.o