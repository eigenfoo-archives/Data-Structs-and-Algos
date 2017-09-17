.PHONY: clean debug run

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS =

SOURCES = sort.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = sort.exe

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
