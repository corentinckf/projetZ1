CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

animation_simple : animation_simple.o 
	$(CC) animation_simple.o $(SDL2) -o  animation_simple

animation_simple.o : animation_simple.c animation_simple.h  
	$(CC) $(OPT) animation_simple.c 

clear :
	rm -f *.o
	
