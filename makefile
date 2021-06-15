
CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

serpents : serpents.o
	$(CC) serpents.o $(OPT) $(SDL2) -o  serpents

serpents.o : serpents.c serpents.h
	$(CC) serpents.c -o

textures.o : textures.c textures.h  
	$(CC) textures.c $(OPT) $(SDL2) -o  textures.o 

clear :
	rm -f *.o