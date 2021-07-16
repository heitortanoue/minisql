all : main.c
	gcc -o prog.exe -c main.c

run :
	./prog.exe

main.c : funcoesheitor.o funcoestorrent.o funcoes.h

funcoesheitor.o : funcoesheitor.c
	gcc -o funcoesheitor.o -c funcoesheitor.c

funcoestorrent.o : funcoestorrent.c
	gcc -o funcoestorrent.o -c funcoestorrent.c

clean :
	rm -f *.o
	rm -f prog
