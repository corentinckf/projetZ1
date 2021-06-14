CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lm
SDL2FLAGS = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
OBJFILES = nomdufichierobjet.o
TARGET = prog

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(SDL2FLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)

