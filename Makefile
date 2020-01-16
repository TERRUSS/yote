CC=gcc
CFLAGS=-Wall
LIBS=-lSDL2 -lSDL2_image -lm
FILES=src/main.c src/vue/graphics.c src/vue/utils.c src/utils/utils.c src/model/game.c src/controler/inputs.c
HEADERS=src/main.h src/vue/graphics.h src/vue/utils.h src/utils/utils.h src/model/game.h src/controler/inputs.h
DIR=build


yote: $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(FILES) -o yote $(LIBS)

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
	rm -f yote
	rm -f *.tar
	rm -rf $(DIR)
