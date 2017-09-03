.PHONY: clean debug run
CC = g++
CFLAGS = -Wall

all: stacks-and-queues

stacks-and-queues: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o $@

clean:
	rm -f src/*.o stacks-and-queues

debug:
	$(CC) $(CFLAGS) -g src/main.cpp -o stacks-and-queues

run:
	./stacks-and-queues
