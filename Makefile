CPP=g++
FLAG=-O3 -std=c++11 

all: sample arp

line: main.o line.o
	$(CPP) -o  main main.o line.o

slack: main.o slack.o
	$(CPP) -o main main.o slack.o

voice: main.o voice.O
	$(CPP) -o main main.o voice.o

sample: main.o sample.o
	$(CPP) -o main main.o sample.o

arp: arp_recv.o
	$(CPP) -o arp arp_recv.o

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

arp_recv.o: arp_recv.cpp
	$(CPP) -c $(FLAG) arp_recv.cpp

clean:; rm -f *.o *~main
