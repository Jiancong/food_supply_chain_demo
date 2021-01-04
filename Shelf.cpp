#include <Shelf.h>

void Shelf::Shelf(TEMPERATURE temp, double decayModifier, int capacity){
	temp_ = temp;
	decayModifier_ = decayModifier;
	capacity_ = capacity;
	buffers_ = make_unique(CircularBuffer<shared_ptr<Order> >)(capacity);
}

void Shelf::SetTemp(TEMPERATURE temp) {
	temp_ = temp;
}

bool Shelf::Full(){
	return buffers_.size() == capacity_ ;
}

int Shelf::GetSize(){
	return buffers_.size();
}

shared_ptr<Order> Shelf::Find(String id) {
	return buffers_.Find(id);
}

bool Shelf::Add(shared_ptr<Order> order) {

	if (buffers_.Full()) return false;

	buffers_.Put(order);

	return true;
}

// Remove the tail element
shared_ptr<Order> Shelf::Remove(){
	if (buffers_.Empty()) return nullptr;
	return buffers_.get();
}

double Shelf::GetDecayModifier(){
	if (temp_ == TEMPERATURE:OVERFLOW) return 2.0;
	else return 1.0;

}

void Shelf::Maintain(){
	buffers_.Maintain();
}
