spell.exe: spellcheck.o hash.o
	g++ -o spell.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.hpp
	g++ -c spellcheck.cpp

hash.o: hash.cpp hash.hpp
	g++ -c hash.cpp

debug:
	g++ -g -o spellDebug.exe spellcheck.cpp hash.cpp

clean:
	rm -rf *.exe *.o *.stackdump *~ *.dSYM/

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
