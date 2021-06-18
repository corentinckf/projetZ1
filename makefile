CC= gcc
OPT  = -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: Y_fenetres serpents textures vie vie_amelioree

Y_fenetres : Y_fenetres.c
	$(CC) Y_fenetres.c $(OPT) $(SDL2) -o  Y_fenetres

serpents : serpents.c
	$(CC) serpents.c $(OPT) $(SDL2) -o  serpents

textures : textures.c
	$(CC) textures.c $(OPT) $(SDL2) -o  textures

vie : vie.c
	$(CC) vie.c $(OPT) $(SDL2) -o  vie

vie_amelioree : vie_amelioree.c
	$(CC) vie_amelioree.c $(OPT) $(SDL2) -o  vie_amelioree

clear :
	rm -f *.o