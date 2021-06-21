CC= gcc
OPT  = -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: tasbin

tasbin : tasbin.c tasbin.h
	$(CC) $< $(OPT) $(SDL2) -o  $@

clear :
	rm -rf $(EXEC)