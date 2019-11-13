yote: main.o
	gcc -o yote main.o

main.o: main.c
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf yote
