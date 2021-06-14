CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lm
OBJFILES = nomdufichierobjet.o
TARGET = prog

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)

