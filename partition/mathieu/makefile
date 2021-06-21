CC=gcc
OPT= -Wall -g

partition : partition.o  liste_chainee.o 
	$(CC) $(OPT) partition.o  liste_chainee.o -o partition

partition.o : partition.c liste_chainee.h
	$(CC) $(OPT) -o partition.o -c partition.c

liste_chainee.o : liste_chainee.c liste_chainee.h
	$(CC) $(OPT) -o liste_chainee.o -c liste_chainee.c 2>/dev/null



clean:
	rm -f *.o

