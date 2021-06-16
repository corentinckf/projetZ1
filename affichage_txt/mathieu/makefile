CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

main : main.o util_sdl.o
	$(CC) main.o util_sdl.o $(SDL2) -o  main

main.o : main.c  
	$(CC) $(OPT) main.c -c

util_sdl.o : util_sdl.c util_sdl.h
	$(CC) $(OPT) util_sdl.c -c

clear :
	rm -f *.o
	