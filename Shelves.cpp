#include "Shelves.h"
#include <iostream>

Shelves::Shelves(){
	shelvesMap_.emplace("COLD", make_shared<Shelf>("COLD", 1, 10));
	shelvesMap_.emplace("FROZEN", make_shared<Shelf>("FROZEN", 1, 10));
	shelvesMap_.emplace("HOT", make_shared<Shelf>("HOT", 1, 10));
	overflowShelf_ = make_shared<Shelf>("OVERFLOW", 2, 15);
}

Shelves::Shelves(int coldSize, int frozenSize, int hotSize, int overflowSize){

	if (coldSize < 0 || frozenSize < 0 || hotSize < 0 || overflowSize < 0) {
		Shelves();
	} else {
		shelvesMap_.emplace("COLD", make_shared<Shelf>("COLD", 1, coldSize));
		shelvesMap_.emplace("FROZEN", make_shared<Shelf>("FROZEN", 1, frozenSize));
		shelvesMap_.emplace("HOT", make_shared<Shelf>("HOT", 1, hotSize));
		overflowShelf_ = make_shared<Shelf>("OVERFLOW", 2, overflowSize);
	}
}

bool Shelves::PrintStatus(){

	cout << "********** Shelves Status Printing ************" << endl;
	
	for (auto& it: shelvesMap_) {
		it.second->PrintStatus();
	}

	overflowShelf_->PrintStatus();

}

shared_ptr<Shelf> Shelves::GetShelf(string temp){
	auto it = shelvesMap_.find(temp);
	if (it != shelvesMap_.end()){
		return it->second;
	} else {
		return overflowShelf_;
	}
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
	shared_ptr<Order> removed = overflowShelf_->RemoveTail();

	overflowShelf_->Add(order);

	// try to find available room
	for(auto iter = shelvesMap_.begin(); iter != shelvesMap_.end(); ++iter)
	{
		shared_ptr<Shelf> shelf = iter->second;
		if (!shelf->Full())
		{
			shelf->Add(removed);
			return;
		}
	}

	cout << "*********** Shelves order discarded ***************" << endl;
	cout << " Order [" << removed->GetId() << "] is discarded." << endl;
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

		if (!it->second->Full()) {
			ret = it->second->Add(order);
			return true;
		}

	} else {
		cerr << "The order temp is invalid, order temp is " << order->GetTemp() << endl;
		return false;
	}

	//cout << "Shelves::AddOrder Single temp shelf is full..." << endl;

	// single temp shelf is full
	ret = overflowShelf_->Add(order);
	if (ret == true) {
		return true;
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

	string temp = "";

	shared_ptr<Order> order = overflowShelf_->Get(orderId);
	if (order != nullptr) {
		return order;
	} else {

		for(auto it = shelvesMap_.begin(); it != shelvesMap_.end(); ++it) {

			shared_ptr<Shelf> shelf = it->second;
			shared_ptr<Order> order = shelf->Remove(orderId);
			if (order != nullptr) {
				return order;
			}
		}

	}

	Maintain();

	return nullptr;
}
