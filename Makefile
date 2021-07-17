all : main.o arquivo_tabela.o nova_string.o
	gcc -o prog.exe arquivo_tabela.o nova_string.o main.o arquivo_tabela.h nova_string.h

run :
	./prog.exe

main.o : main.c
	gcc -o main.o -c main.c

arquivo_tabela.o : arquivo_tabela.c arquivo_tabela.h
	gcc -o arquivo_tabela.o -c arquivo_tabela.c

nova_string.o : nova_string.c nova_string.h
	gcc -o nova_string.o -c nova_string.c

clean :
	-del -f *.exe *.o