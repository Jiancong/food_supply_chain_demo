#include "Shelf.h"
#include <iostream>
#include <memory>

Shelf::Shelf(string temp, double decayModifier, int capacity){
	temp_ = temp;
	decayModifier_ = decayModifier;
	capacity_ = capacity;
	buffers_ = unique_ptr<CircularBuffer>(new CircularBuffer(capacity));
}

void Shelf::SetTemp(string temp) {
	temp_ = temp;
}

bool Shelf::Full(){
	return buffers_->Size() == capacity_ ;
}

int Shelf::GetSize(){
	return buffers_->Size();
}

shared_ptr<Order> Shelf::Find(string orderId) {
	return buffers_->Find(orderId);
}

bool Shelf::PrintStatus() {

	cout << "Shelf=" << GetTemp() <<", size=" << GetSize() << endl;
	buffers_->PrintStatus();
	return true;

}

bool Shelf::Add(shared_ptr<Order> order) {

	if (buffers_->Full()) {
		cout << "the buffer is full, returned." << endl;
		return false;
	}

	buffers_->Put(order);

	cout << "After add operation, the size is " << GetSize() << endl;

	return true;
}

// Remove the specific element
shared_ptr<Order> Shelf::Remove(string orderId){
	if (buffers_->Empty()) return nullptr;
	return buffers_->Get(orderId);
}

// Remove the tail element
shared_ptr<Order> Shelf::Remove(){
	if (buffers_->Empty()) return nullptr;
	return buffers_->Get();
}

double Shelf::GetDecayModifier(){
	if (temp_ == "OVERFLOW") return 2.0;
	else return 1.0;
}

void Shelf::Maintain(){
	buffers_->Maintain(GetDecayModifier());
}

string Shelf::GetTemp(){
	return temp_;
}
