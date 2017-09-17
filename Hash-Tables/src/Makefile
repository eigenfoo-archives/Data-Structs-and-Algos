.PHONY: clean debug run

CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS =

SOURCES = hash.cpp spellcheck.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = spell.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) debug.exe *.stackdump *~ *.dSYM/

debug:
	$(CC) $(CFLAGS) -g -o debug.exe $(SOURCES)

run:
	./$(EXECUTABLE)
