CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o perso.o affichage.o
	$(CC) main.o perso.o affichage.o $(SDL2) -o  prog

main.o : main.c main.h  
	$(CC) $(OPT) main.c 

perso.o : perso.c perso.h  
	$(CC) $(OPT) perso.c 

affichage.o : affichage.c affichage.h  main.h
	$(CC) $(OPT) affichage.c 

item.o : item.c   main.h
	$(CC) $(OPT) item.c 

clear :
	rm -f *.o