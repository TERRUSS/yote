CC=gcc
CFLAGS=-Wall
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lm

FILES_MODEL=src/model/game.c src/model/ia.c
FILESH_MODEL=src/model/game.h src/model/ia.h
FILES_VUE=src/vue/graphics.c src/vue/utils.c src/vue/menu.c
FILESH_VUE=src/vue/graphics.h src/vue/utils.h src/vue/menu.h
FILES_CONTROLER=src/controler/inputs.c src/controler/game.c src/controler/save.c
FILESH_CONTROLER=src/controler/inputs.h src/controler/game.h src/controler/save.h

FILES_UTILS=src/utils/utils.c
FILESH_UTILS=src/utils/utils.h


FILES=src/main.c
HEADERS=src/main.h

FILES += $(FILES_MODEL) $(FILES_VUE) $(FILES_CONTROLER) $(FILES_UTILS)
HEADERS += $(FILESH_MODEL) $(FILESH_VUE) $(FILESH_CONTROLER) $(FILESH_UTILS)

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
