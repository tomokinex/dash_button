CPP=g++
FLAG=-O3 -std=c++11 

all: sample

line: main.o line.o
	$(CPP) -o  main main.o line.o

slack: main.o slack.o
	$(CPP) -o main main.o slack.o

voice: main.o voice.O
	$(CPP) -o main main.o voice.o

sample: main.o sample.o
	$(CPP) -o main main.o sample.o

main.o: main.cpp defines.hpp
	$(CPP) -c $(FLAG) main.cpp 

line.o: line.cpp
	$(CPP) -c $(FLAG) line.cpp

slack.o: slack.cpp
	$(CPP) -c $(FLAG) slack.cpp

voice.o: voice.cpp
	$(CPP) -c $(FLAG) voice.cpp

sample.o: sample.cpp
	$(CPP) -c $(FLAG) sample.cpp

clean:; rm -f *.o *~main
