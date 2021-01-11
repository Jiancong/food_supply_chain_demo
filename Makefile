INCLUDE= -I. -I./util

CPPFLAGS=-g -pipe -Wno-deprecated -std=c++11
CFLAG= -g -c -pipe -fPIC -Wno-deprecated -std=c++11  

CPP=g++
CC=g++

OBJS= Kitchen.o Courier.o Shelves.o Shelf.o Order.o CircularBuffer.o util/cJSON.o Main.o

Kitchen: $(OBJS) 
	$(CPP) $(CPPFLAGS) -o $@ $(INCLUDE) $^ -lpthread

clean:
	rm -f *.o
	rm -f Kitchen
