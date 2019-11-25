CC=gcc
CFLAGS=-Wall
LIBS=-lSDL2
FILES=main.c vue/game.c
HEADERS=header.h vue/header.h
DIR=build

#Cible generique pour Linux
%: %.c
	rm -f $@
	$(CC) $(CFLAGS) graphics.o $@.c -o $@ $(LIBS)


main: main.c graphics.o $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) graphics.o main.c $(FILES) -o main $(LIBS)

tar: clean
	rm -rf $(DIR)
	mkdir $(DIR)
	cp exemple.c $(DIR)
	cp lib/graphics.c $(DIR)
	cp lib/graphics.h $(DIR)
	cp lib/couleur.h $(DIR)
	cp exo1.1.c $(DIR)
	cp Makefile $(DIR)
	cp lib/*.ttf $(DIR)
	tar cvf $(DIR).tar $(DIR)
	rm -rf $(DIR)

clean:
	rm -f *core
	rm -f *.o
	rm -f lib/police.h
	rm -f main
	rm -f *.tar
	rm -rf $(DIR)