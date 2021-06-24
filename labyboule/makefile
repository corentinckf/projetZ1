CC= gcc
OPT  = -Wextra -Wall -g
LDFLAGS = -lm
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
EXEC = labyrinthe_arborescent

all: $(EXEC)

gestion_boules : gestion_boules.c gestion_boules.h
	$(CC) $< $(OPT) -lm $(LDFLAGS) $(SDL2) -o  $@

clear :
	rm -rf $(EXEC)