INCLUDE= -I. -I./util

CPPFLAGS=-g -fPIC -pipe -Wno-deprecated -std=c++11
CFLAG= -g -c -fPIC -pipe -Wno-deprecated -std=c++11  

CPP=g++
CC=g++

OBJS= Kitchen.o Courier.o Shelves.o Shelf.o Order.o CircularBuffer.o util/cJSON.o Main.o
TESTOBJS = Order.o CircularBuffer.o tests/CircularBufferTest.o

.PHONY: test clean

test: CircularBufferTest

Kitchen: $(OBJS) 
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lpthread

CircularBufferTest: $(TESTOBJS)
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lgtest -lpthread

clean:
	rm -f *.o util/*.o
	rm -f Kitchen
