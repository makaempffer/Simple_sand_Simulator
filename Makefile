CC = gcc
CFLAGS = -Wall -Iraylib/src -Lraylib/src -lraylib -lm

SOURCES = src/main.c 
HEADERS = src/constants.h src/sand.h
EXECUTABLE = game

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

clean:
	rm -f $(EXECUTABLE)
