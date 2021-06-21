CC= gcc
OPT  = -Wextra -Wall -g
LDFLAGS = -lm
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
EXEC = connexe

all: connexe

connexe : arborescence.c arborescence.h connexe.c connexe.h
	$(CC) arborescence.c connexe.c $(OPT) $(LDFLAGS) $(SDL2) -o  $@

clear :
	rm -rf $(EXEC)