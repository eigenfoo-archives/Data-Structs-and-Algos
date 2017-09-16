.PHONY: clean debug run

CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS =

SOURCES = sort.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = sort.exe

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
