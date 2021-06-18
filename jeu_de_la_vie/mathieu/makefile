CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

jeu_de_la_vie : jeu_de_la_vie.o 
	$(CC) jeu_de_la_vie.o $(SDL2) -o  jeu_de_la_vie

jeu_de_la_vie.o : jeu_de_la_vie.c jeu_de_la_vie.h  
	$(CC) $(OPT) jeu_de_la_vie.c 

clear :
	rm -f *.o
	
