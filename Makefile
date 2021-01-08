INCLUDE= -I./util

CPPFLAGS=-O3 -pipe -Wno-deprecated -std=c++11

CPP=g++

OBJS=Kitchen.o Courier.o Shelves.o Shelf.o Order.o CircularBuffer.o

Kitchen: $(OBJS) 
	$(CPP) $(CPPFLAGS) -o $@ -lpthread
