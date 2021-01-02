#include <Shelves.h>

Shelves::Shelves(){
	coldShelf_ = make_unique<Shelf>(TERMPERATURE:COLD, 10, 1);
	frozenShelf_ = make_unique<Shelf>(TERMPERATURE:FROZEN, 10, 1);
	hotShelf_ = make_unique<Shelf>(TERMPERATURE:HOT, 10, 1);
	overflowShelf_ = make_unique<Shelf>(TERMPERATURE:OVERFLOW, 15, 2);
}

bool Shelves::findAvailable(){
	if (!coldShelf_.Full()) 
}

void Shelves::processOverflow(){
	unique_ptr<Order> picked = overflowShelf_.Pick();
	if (!coldShelf_.Full()) {
		coldShelf_.Add(picked);
		return ;
	}

	if (!hotShelf_.Full()) {
		hotShelf_.Add(picked);
		return ;
	}

	if (!frozenShelf_.Full()) {
		frozenShelf_.Add(picked);
		return ;
	}

	// drop it as wasted and return.
	return ;
}

bool Shelves::Add(unique_ptr<Order> order){
	bool ret = false;
	if (order.GetTemp() == "COLD") {
		ret = coldShelf_.Add(order);
	} else if (order.GetTemp() == "HOT") {
		ret = hotShelf_.Add(order);
	} else if (order.GetTemp() == "FROZEN") {
		ret = frozenShelf_.Add(order);
	}

	if (ret == false) {
		ret = overflowShelf_.Add(order);
	} else {
		return true;
	}

	// overflowShelf is full.
	if (ret == false) {
		processOverflow();
		ret = overflowShelf_.Add(order);
	}

	return ret;

}
