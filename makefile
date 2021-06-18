CC= gcc
OPT  = -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: Y_fenetres serpents textures vie vie_amelioree tasbin

tasbin : tasbin.c tasbin.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

Y_fenetres : Y_fenetres.c Y_fenetres.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

serpents : serpents.c serpents.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

textures : textures.c textures.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

vie : vie.c vie.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

vie_amelioree : vie_amelioree.c vie_amelioree.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

clear :
	rm -rf $(EXEC)