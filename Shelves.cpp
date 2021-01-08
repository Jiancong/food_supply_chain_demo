#include "Shelves.h"
#include <iostream>

Shelves::Shelves(){
	shelves_.emplace("COLD", make_shared<Shelf>("COLD", 10, 1));
	shelves_.emplace("FROZEN", make_shared<Shelf>("FROZEN", 10, 1));
	shelves_.emplace("HOT", make_shared<Shelf>("HOT", 10, 1));
	overflowShelf_ = make_shared<Shelf>("OVERFLOW", 15, 2);
}

Shelves::Maintain(){

}

void Shelves::processOverflow(shared_ptr<Order> order){

	// remove the tail element from overflow
	shared_ptr<Order> removed = overflowShelf_->Remove();

	if (removed != nullptr) {
		shelfMapper_.erase(removed->GetId());
	}
	
	overflowShelf_->Add(order);
	shelfMapper_.emplace(order->GetId(), ToUpper(order->GetTemp()));

	// try to find available room
	for(auto iter = shelves_.begin(); iter != shelves_.end(); ++iter)
	{
		shared_ptr<Shelf> shelf = iter->second;
		if (!shelf->Full())
		{
			shelf->Add(removed);
			shelfMapper_.emplace(removed->GetId(), shelf->GetTemp() );
			return;
		}
	}

	return ;
}

// Add order in specific temp shelf, if 
// that was full, try to put it in overflow shelf.
// If the overflow is full, go to process func.
bool Shelves::AddOrder(shared_ptr<Order> order){

	bool ret = false;

	auto it = shelves_.find(ToUpper(order->GetTemp()));

	if (it != shelves_.end()) {
		ret = it->second->Add(order);
		shelfMapper_.emplace(order->GetId(), ToUpper(order->GetTemp()));
		return true;
	}

	// single temp shelf is full
	if (ret == false) {
		ret = overflowShelf_->Add(order);

		// enter in overflow 
		if (ret == true) {
			shelfMapper_.emplace(order->GetId(), ToUpper(order->GetTemp()));
			return true;
		}
	} 

	// overflowShelf is full.
	if (ret == false) {
		processOverflow(order);
		ret = true;
	}
	return ret;
}

// Remove from shelves
shared_ptr<Order> Shelves::Remove(string orderId){

	auto it = shelfMapper_.find(orderId);
	string temp = "";
	if (it != shelfMapper_.end()){
		temp = it->second;
	}

	if (temp == "OVERFLOW") {
		shared_ptr<Order> order = overflowShelf_->Find(orderId);
		if (order != nullptr) {

			shared_ptr<Order> order = overflowShelf_->Remove(orderId);
			if (order != nullptr) {
				shelfMapper_.erase(orderId);
				return order;
			} else {
				cerr << "ERROR: overflow shelf's accelerator *DOES NOT* match the shelf status. OrderId:" << orderId << endl;
				return nullptr;
			}
		}
	} else {
		auto it2 = shelves_.find(temp);
		shared_ptr<Shelf> shelf = it2->second;
		shared_ptr<Order> order = shelf->Remove(order->GetId());
		if (order!=nullptr) {
			shelfMapper_.erase(orderId);
			return order;
		} else {
			cerr << "ERROR: single shelf's accelerator *DOES NOT* match the shelf status. Shelf'name: " << temp << ", orderId:" << orderId << endl;;
			return nullptr;
		}
	}
}
