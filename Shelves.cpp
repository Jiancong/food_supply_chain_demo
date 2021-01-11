#include "Shelves.h"
#include <iostream>

Shelves::Shelves(){
	shelvesMap_.emplace("COLD", make_shared<Shelf>("COLD", 1, 10));
	shelvesMap_.emplace("FROZEN", make_shared<Shelf>("FROZEN", 1, 10));
	shelvesMap_.emplace("HOT", make_shared<Shelf>("HOT", 1, 10));
	overflowShelf_ = make_shared<Shelf>("OVERFLOW", 2, 15);
}

bool Shelves::PrintStatus(){

	cout << "********** Shelves Status Printing ************" << endl;
	
	for (auto& it: shelvesMap_) {
		it.second->PrintStatus();
	}

	overflowShelf_->PrintStatus();

}

void Shelves::Maintain(){

	cout << endl;
	cout << "********** Shelves is Maintaining ************" << endl;

	overflowShelf_->Maintain();

	for (auto& it: shelvesMap_) {
		it.second->Maintain();
	}
}

void Shelves::ProcessOverflow(shared_ptr<Order> order){

	// remove the tail element from overflow
	shared_ptr<Order> removed = overflowShelf_->Remove();

	if (removed != nullptr) {
		idMap_.erase(removed->GetId());
	}
	
	overflowShelf_->Add(order);
	idMap_.emplace(order->GetId(), ToUpper(order->GetTemp()));

	// try to find available room
	for(auto iter = shelvesMap_.begin(); iter != shelvesMap_.end(); ++iter)
	{
		shared_ptr<Shelf> shelf = iter->second;
		if (!shelf->Full())
		{
			shelf->Add(removed);
			idMap_.emplace(removed->GetId(), shelf->GetTemp() );
			return;
		}
	}
	return ;
}

// Add order in specific temp shelf, if 
// that was full, try to put it in overflow shelf.
// If the overflow is full, go to process func.
bool Shelves::AddOrder(shared_ptr<Order> order){

	cout << endl;
	cout << "******** Shelves AddOrder calling ****** " << endl;
	PrintStatus();

	Maintain();

	bool ret = false;

	//cout << "order temp: " << order->GetTemp() << endl;

	auto it = shelvesMap_.find(ToUpper(order->GetTemp()));

	if (it != shelvesMap_.end()) {

		//cout << "shelf size:" << it->second->GetSize() << endl;

		if (!it->second->Full()) {
			ret = it->second->Add(order);
			idMap_.emplace(order->GetId(), ToUpper(order->GetTemp()));
			return true;
		}

	} else {
		cerr << "The order temp is invalid, order temp is " << order->GetTemp() << endl;
		return false;
	}

	//cout << "Shelves::AddOrder Single temp shelf is full..." << endl;

	// single temp shelf is full
	if (ret == false) {
		ret = overflowShelf_->Add(order);

		// enter in overflow 
		if (ret == true) {
			idMap_.emplace(order->GetId(), ToUpper(order->GetTemp()));
			return true;
		}
	} 

	//cout << "Shelves::AddOrder overflow shelf is full..." << endl;

	// overflowShelf is full.
	if (ret == false) {
		ProcessOverflow(order);
		ret = true;
	}
	return ret;
}

// Remove from shelves
shared_ptr<Order> Shelves::Remove(string orderId){

	cout << endl;
	cout << "*************  Shelves::Remove is calling *************" << endl;

	PrintStatus();


	auto it = idMap_.find(orderId);
	string temp = "";
	if (it != idMap_.end()){
		temp = it->second;
	}

	if (temp == "OVERFLOW") {
		shared_ptr<Order> order = overflowShelf_->Find(orderId);
		if (order != nullptr) {

			shared_ptr<Order> order = overflowShelf_->Remove(orderId);
			if (order != nullptr) {
				idMap_.erase(orderId);
				return order;
			} else {
				cerr << "ERROR: overflow shelf's accelerator *DOES NOT* match the shelf status. OrderId:" << orderId << endl;
				return nullptr;
			}
		}
	} else {
		auto it2 = shelvesMap_.find(temp);
		shared_ptr<Shelf> shelf = it2->second;

		shared_ptr<Order> order = shelf->Remove(orderId);
		if (order!=nullptr) {
			idMap_.erase(orderId);
			return order;
		} else {
			cerr << "ERROR: single shelf's accelerator *DOES NOT* match the shelf status. Shelf'name: " << temp << ", orderId:" << orderId << endl;;
			return nullptr;
		}
	}

	Maintain();
}
