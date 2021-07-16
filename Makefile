all : main.o funcoesheitor.o funcoestorrent.o funcoes.h
	gcc -o prog.exe funcoesheitor.o funcoestorrent.o main.o

run :
	./prog.exe

main.o : main.c
	gcc -o main.o -c main.c

funcoesheitor.o : funcoesheitor.c
	gcc -o funcoesheitor.o -c funcoesheitor.c

funcoestorrent.o : funcoestorrent.c
	gcc -o funcoestorrent.o -c funcoestorrent.c

clean :
	-del -f *.exe *.o
