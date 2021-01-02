#ifndef __SHELVES_H__
#define __SHELVES_H__

#include <list>
#include <string>
#include "Shelf.h"
#include "Order.h"

using namespace std;

class Shelves {

private:
	unique_ptr<Shelf> coldShelf_;
	unique_ptr<Shelf> hotShelf_;
	unique_ptr<Shelf> frozenShelf_;
	unique_ptr<Shelf> overflowShelf_;

public:
	
	Shelves();
	bool Add(unique_ptr<Order>);
	Order* Remove();
	void processOverflow();
};
#endif
