CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : labyrinthe.o kruskal.o connexe.o partition.o liste_chainee.o 
	$(CC) labyrinthe.o kruskal.o connexe.o partition.o liste_chainee.o  $(SDL2) -o prog


labyrinthe.o : labyrinthe.c labyrinthe.h
	$(CC) $(OPT) -o labyrinthe.o -c labyrinthe.c

kruskal.o : kruskal.c kruskal.h
	$(CC) $(OPT) -o kruskal.o -c kruskal.c

connexe.o : connexe.c connexe.h
	$(CC) $(OPT) -o connexe.o -c connexe.c

partition.o : partition.c liste_chainee.h
	$(CC) $(OPT) -o partition.o -c partition.c

liste_chainee.o : liste_chainee.c liste_chainee.h
	$(CC) $(OPT) -o liste_chainee.o -c liste_chainee.c 2>/dev/null

clean:
	rm -f *.o

