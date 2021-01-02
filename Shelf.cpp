#include <Shelf.h>

void Shelf::Shelf(TEMPERATURE temp, double decayModifier, int capacity){
	temp_ = temp;
	decayModifier_ = decayModifier;
	capacity_ = capacity;
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

bool Shelf::Add(unique_ptr<Order> order) {

	lock_guard<mutex> lock(mutex_);
	if (buffers_.size() == capacity_) return false;

	buffers_.insert(std::move(order));

	return true;

}

// Remove the one with smallest value in the shelf
bool Shelf::Remove(){
	lock_guard<mutex> lock(mutex_);
	if (buffers_.size() == 0) return false;

	for (it_=buffers_.begin(); it_ != buffers_.end(); )
	{
		if (it_.GetValue() <= 0) {
			it_ = buffers_.erase(it_);
		} else {
			++it;
		}
	}

	if (buffers_.size() == capacity_) return false;

	return true;
}

double Shelf::GetDecayModifier(){
	if (temp_ == TEMPERATURE:OVERFLOW) return 2.0;
	else return 1.0;

}


