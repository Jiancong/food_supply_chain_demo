#ifndef __SHELVES_H__
#define __SHELVES_H__

#include <list>
#include <string>
#include "Shelf.h"
#include "Order.h"

using namespace std;

class Shelves {

private:
	// composite
	unordered_map<TEMPERATURE, shared_ptr<Shelf> > shelves_;
	shared_ptr<Shelf> overflowShelf_;
	// use this as we need to keep orders in specific order.
	unique_ptr<CircularBuffer<String> > ids_;

	void processOverflow();

public:
	
	Shelves();
	bool Add(shared_ptr<Order>);
	shared_ptr<Order> Remove();
};
#endif
