.PHONY: clean debug run

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS =

SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) debug.exe *.stackdump *~ *.dSYM/

debug:
	$(CXX) $(CXXFLAGS) -g -o debug.exe $(SOURCES)

run:
	./$(EXECUTABLE)
