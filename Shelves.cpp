#include <Shelves.h>

Shelves::Shelves(){
	shelves_.insert(TEMPERATURE:COLD, make_shared<Shelf>(TEMPERATURE:COLD, 10, 1));
	shelves_.insert(TEMPERATURE:COLD, make_shared<Shelf>(TEMPERATURE:FROZEN, 10, 1));
	shelves_.insert(TEMPERATURE:COLD, make_shared<Shelf>(TEMPERATURE:HOT, 10, 1));

	overflowShelf_ = make_shared<Shelf>(TEMPERATURE:OVERFLOW, 15, 2);

	ids_ = make_unique<CircularBuffer<String> >(45);
}

// Remove earliest order in overflow, try to put in 
// some shelf, otherwise discard the order.
void Shelves::processOverflow(shared_ptr<Order> order){

	shared_ptr<Order> removed = overflowShelf_.Remove();
	overflowShelf_.Add(order);

	for(auto iter = shelves_.begin(); iter != shelves_.end(); ++iter)
	{
		shared_ptr<Shelf> shelf = iter->second;
		if (!shelf.Full())
		{
			shelf.Add(removed);
			return;
		}
	}

	return ;
}

// Add order in specific temp shelf, if 
// that was full, try to put it in overflow shelf.
// If the overflow is full, go to process func.
bool Shelves::Add(shared_ptr<Order> order){
	bool ret = false;

	auto it = shelves_.find(order.GetTemp());

	if (it != shelves_.end()) {
		ret = it->second.Add(order);
	}

	if (ret == false) {
		ret = overflowShelf_.Add(order);
	} else {
		return true;
	}

	// overflowShelf is full.
	if (ret == false) {
		processOverflow(order);
		ret = true;
	}
	return ret;
}

// Remove from shelves
shared_ptr<Order> Shelves::Remove(){

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
