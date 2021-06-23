CC= gcc
OPT  = -Wextra -Wall -g
LDFLAGS = -lm
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
EXEC = kruskal

all: $(EXEC)

connexe : arborescence.c arborescence.h connexe.c connexe.h
	$(CC) arborescence.c connexe.c $(OPT) -lm $(LDFLAGS) $(SDL2) -o  $@

kruskal : kruskal.c kruskal.h arborescence.c arborescence.h connexe.c connexe.h
	$(CC) connexe.c arborescence.c kruskal.c $(OPT) -lm $(LDFLAGS) $(SDL2) -o  $@

clear :
	rm -rf $(EXEC)