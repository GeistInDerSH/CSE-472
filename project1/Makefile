CC = g++
CFLAGS = -std=c++11 -O2
FILES := $(wildcard *.cpp)

all : comparison

comparison : main.o compare.o
	$(CC) $(CFLAGS) -o $@ $+ -lm

%.o : %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clear :
	rm -f *.o
	rm -f comparison

remake :
	rm -f *.o
	rm -f comparison
	comparison
