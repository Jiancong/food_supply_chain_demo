INCLUDE= -I. -I./util

CPPFLAGS=-g -fPIC -pipe -Wno-deprecated -std=c++11
CFLAG= -g -c -fPIC -pipe -Wno-deprecated -std=c++11  

CPP=g++
CC=g++

OBJS= Kitchen.o Courier.o Shelves.o Shelf.o Order.o CircularBuffer.o util/cJSON.o Main.o
TESTOBJS = Order.o CircularBuffer.o Shelf.o

.PHONY: test clean Kitchen

all: Kitchen

test: CircularBufferTest ShelfTest

Kitchen: $(OBJS) 
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lpthread

CiruclarBufferTest : $(TESTOBJS) tests/CircularBufferTest.o
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lgtest -lpthread

ShelfTest : $(TESTOBJS) tests/ShelfTest.o
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lgtest -lpthread

clean:
	rm -f *.o util/*.o
	rm -f Kitchen
