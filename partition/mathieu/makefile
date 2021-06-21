CC=gcc
OPT= -Wall -g

prog : kruskal.o connexe.o partition.o  liste_chainee.o 
	$(CC) $(OPT) kruskal.o connexe.o partition.o  liste_chainee.o -o prog

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

