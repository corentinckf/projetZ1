CC = gcc
OPT  = -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
EXEC = chef_oeuvre

all: $(EXEC)

chef_oeuvre : chef_oeuvre.c
	$(CC) chef_oeuvre.c $(OPT) $(SDL2) -o  chef_oeuvre

clean:
	rm -rf $(EXEC)