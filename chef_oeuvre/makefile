CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o perso.o
	$(CC) main.o perso.o $(SDL2) -o  prog

main.o : main.c main.h  
	$(CC) $(OPT) main.c 

perso.o : perso.c perso.h  
	$(CC) $(OPT) perso.c 

#util_sdl.o : util_sdl.c util_sdl.h  
#	$(CC) $(OPT) util_sdl.c 


clear :
	rm -f *.o