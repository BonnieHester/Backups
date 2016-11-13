all: repl

run: repl
	./repl

repl: myProcess.o repl.o
	g++ -Wall -g -o repl myProcess.o repl.o

repl.o: repl.cpp
	g++ -Wall -std=c++14 -c -g -O0 -pedantic-errors repl.cpp

myProcess.o: myProcess.cpp
	g++ -Wall -std=c++14 -c -g -O0 -pedantic-errors myProcess.cpp

clean:
	rm -f repl.o
	rm -f repl.cpp
	rm -f myProcess.o
	rm -f myProcess.cpp
