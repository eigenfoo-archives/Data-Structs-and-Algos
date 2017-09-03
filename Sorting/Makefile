.PHONY: clean debug run
CC = g++
CFLAGS = -Wall

all: sort

sort: src/sort.cpp
	$(CC) $(CFLAGS) src/sort.cpp -o $@

clean:
	rm -f src/*.o sort

debug:
	$(CC) $(CFLAGS) -g src/sort.cpp -o sort

run:
	./sort
