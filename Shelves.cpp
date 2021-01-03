#include <Shelves.h>

Shelves::Shelves(){
	coldShelf_ = make_unique<Shelf>(TERMPERATURE:COLD, 10, 1);
	frozenShelf_ = make_unique<Shelf>(TERMPERATURE:FROZEN, 10, 1);
	hotShelf_ = make_unique<Shelf>(TERMPERATURE:HOT, 10, 1);
	overflowShelf_ = make_unique<Shelf>(TERMPERATURE:OVERFLOW, 15, 2);
	ids_ = make_unique<CircularBuffer<String> >(45);
}


void Shelves::processOverflow(unique_ptr<Order> order){

	unique_ptr<Order> removed = overflowShelf_.Remove();
	overflowShelf_.Add(order);

	if (!coldShelf_.Full()) {
		coldShelf_.Add(removed);
		return ;
	}

	if (!hotShelf_.Full()) {
		hotShelf_.Add(removed);
		return ;
	}

	if (!frozenShelf_.Full()) {
		frozenShelf_.Add(removed);
		return ;
	}

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
		processOverflow(order);
	}

	return ret;

}

// Remove from shelves
unique_ptr<Order> Shelves::Remove(){
	if (ids_.Empty()) return nullptr;
	else {
		// find the earliest arrived.
		String id = ids_.Get();

		unique_ptr<Order> order = frozenShelf_.Find(id);
		if (order == nullptr) {
			order = hotShelf_.Find(id);
		} else {
			return order;
		}
		
		if (order == nullptr) {
			order = coldShelf_.Find(id);
		} else {
			return order;
		}

		if (order == nullptr) {
			order = overflowShelf_.Find(id);
		} else {
			return order;
		}

		return order;

	}
}
