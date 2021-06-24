CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lm
OBJFILES = perso.o
SDL2FLAGS = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
TARGET = prog

prog : main.o parcours_graphe.o labyrinthe.o kruskal.o connexe.o partition.o liste_chainee.o tas_binaire.o gestion_map.o 
	$(CC) main.o parcours_graphe.o labyrinthe.o kruskal.o connexe.o partition.o liste_chainee.o tas_binaire.o gestion_map.o $(SDL2) -o prog

main.o : main.c const.h
	$(CC) $(OPT) -o main.o -c main.c

parcours_graphe.o : parcours_graphe.c parcours_graphe.h
	$(CC) $(OPT) -o parcours_graphe.o -c parcours_graphe.c

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

tas_binaire.o : tas_binaire.c tas_binaire.h
	$(CC) $(OPT) -o tas_binaire.o -c tas_binaire.c

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(SDL2FLAGS)

gestion_map.o : gestion_map.c gestion_map.h
	$(CC) $(OPT) -o gestion_map.o -c gestion_map.c


clean:
	rm -f $(OBJFILES) $(TARGET)