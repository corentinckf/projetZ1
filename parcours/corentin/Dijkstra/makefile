CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lm
OBJFILES = main.o partition.o lch.o connexe.o kruskal.o graphe.o labyrinth.o dijsktra.o
SDL2FLAGS = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
TARGET = prog

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(SDL2FLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)

