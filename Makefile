INCLUDE= -I. -I./util

DEBUG=

ifdef DEBUG
CPPFLAGS=-g -DDEBUG -fPIC -pipe -Wno-deprecated -std=c++11
CFLAG= -g -DDEBUG -c -fPIC -pipe -Wno-deprecated -std=c++11  
else
CPPFLAGS=-O3 -fPIC -pipe -Wno-deprecated -std=c++11
CFLAG= -O3 -c -fPIC -pipe -Wno-deprecated -std=c++11  
endif

CPP=g++
CC=g++

OBJS= Kitchen.o Courier.o Shelves.o Shelf.o Order.o CircularBuffer.o util/cJSON.o Main.o
TESTOBJS = Order.o CircularBuffer.o Shelf.o Shelves.o 

.PHONY: test clean Kitchen

all: Kitchen

test: CircularBufferTest ShelfTest ShelvesTest 

Kitchen: $(OBJS) 
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lpthread

CircularBufferTest : $(TESTOBJS) tests/CircularBufferTest.o
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lgtest -lpthread

ShelfTest : $(TESTOBJS) tests/ShelfTest.o
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lgtest -lpthread

ShelvesTest : $(TESTOBJS) tests/ShelvesTest.o
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lgtest -lpthread


clean:
	rm -f *.o util/*.o tests/*.o
	rm -f Kitchen CircularBufferTest ShelfTest ShelvesTest
