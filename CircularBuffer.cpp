#include "CircularBuffer.h"
#include <iostream>

void CircularBuffer::Reset()
{
	lock_guard<mutex> lock(mutex_);
	head_ = tail_;
	full_ = false;
}

bool CircularBuffer::Empty() const
{
	//if head and tail are equal, we are empty
	return (!full_ && (head_ == tail_));
}

bool CircularBuffer::Full() const
{
	//If tail is ahead the head by 1, we are full
	return full_;
}

size_t CircularBuffer::Capacity() const
{
	return max_size_;
}

size_t CircularBuffer::Size() const
{
	size_t size = max_size_;

	if(!full_)
	{
		if(head_ >= tail_)
		{
			size = head_ - tail_;
		}
		else
		{
			size = max_size_ + head_ - tail_;
		}
	}

	return size;
}

void CircularBuffer::Put(shared_ptr<Order> item)
{
	lock_guard<mutex> lock(mutex_);

	//cout << "CircularBuffer::Put, head_: " << head_ << endl;
	//cout << "max_size_:" << max_size_ << endl;

	buf_[head_] = item;

	if(full_)
	{
		tail_ = (tail_ + 1) % max_size_;
	}

	head_ = (head_ + 1) % max_size_;

	full_ = head_ == tail_;
	//cout << "After Put, head_:" << head_ << ", tail_:" << tail_ << ", max_size_:" << max_size_ << endl;
}

void CircularBuffer::SwapTail(int index) {
	shared_ptr<Order> tmp = buf_[index];
	buf_[index] = buf_[tail_];
	buf_[tail_] = tmp;
	tail_ = (tail_ + 1) % max_size_;
}

void CircularBuffer::PrintStatus(){

	if (Empty()) return ;

	cout << "\ttail_:" << tail_ << ", head_:" << head_ << endl;

	if (head_ > tail_) {


		int cnt = 0;
		for (int index = tail_; index != head_; index++) {
			cout << "\t" << cnt++ << "." << buf_[index]->GetId() << endl;
		}
		cout << endl;
	} else {
		int cnt = 0;
		for (int index = tail_; index < max_size_; index++) {
			cout << "\t" << cnt++ << "." << buf_[index]->GetId() << endl;
		}

		for (int index = 0; index < head_; index++) {
			cout << "\t" << cnt++ << "." << buf_[index]->GetId() << endl;
		}
	}

}

shared_ptr<Order> CircularBuffer::Find(string id){
	return Get(id);
}

// Get the specfic element
shared_ptr<Order> CircularBuffer::Get(string id) {
	lock_guard<mutex> lock(mutex_);
	if (Empty()) return nullptr;

	if (head_ > tail_) {

		for (int index = tail_; index != head_; index++) {
			if (buf_[index]->GetId() == id) {
				shared_ptr<Order> ret_ptr = buf_[index];
				SwapTail(index);
				return ret_ptr;
			}
		}
	} else {
		for (int index = tail_; index < max_size_; index++) {
			if (buf_[index]->GetId() == id) {

				shared_ptr<Order> ret_ptr = buf_[index];
				SwapTail(index);
				return ret_ptr;
			}
		}

		for (int index = 0; index < head_; index++) {
			if (buf_[index]->GetId() == id ) {
				shared_ptr<Order> ret_ptr = buf_[index];
				SwapTail(index);
				return ret_ptr;
			}
		}
	}
	return nullptr;
}

// Get the last element
shared_ptr<Order> CircularBuffer::Get()
{
	lock_guard<mutex> lock(mutex_);

	if(Empty())
	{
		return nullptr;
	}

	//Read data and advance the tail (we now have a free space)
	auto val = buf_[tail_];
	full_ = false;
	tail_ = (tail_ + 1) % max_size_;

	return val;
}

void CircularBuffer::Invalidate(int index, double decayModifier) {

	chrono::steady_clock::time_point now = chrono::steady_clock::now();

	int seconds = std::chrono::duration_cast<std::chrono::seconds>(now - buf_[index]->GetBegin()).count();

	double value = (buf_[index]->GetShelfLife() - seconds - buf_[index]->GetDecayRate() * seconds * decayModifier)/buf_[index]->GetShelfLife();

	// this element should be wasted.
	if (value <= 0.0) {

		cout << endl;
		cout << "*********** Order maintainance **************" << endl;
		cout << "Order : [" << buf_[index]->GetId() << "] is discarded ...." << endl;
		cout << endl;

		// swap the index element with tailed.
		shared_ptr<Order> tmp = buf_[tail_];
		buf_[tail_] = buf_[index];
		buf_[index] = tmp;
		tail_ = (tail_+1) % max_size_ ;

	}
}

bool CircularBuffer::Maintain(double decayModifier){
	lock_guard<mutex> lock(mutex_);

	if (Empty())
	{
		return false;
	}

	if (head_ > tail_) {

		for( int index = tail_; index < head_; index++) {
			Invalidate(index, decayModifier);
		}
	} 

	if (tail_ > head_) {
		for( int index = tail_; index < max_size_; index++) {
			Invalidate(index, decayModifier);
		}

		for (int index = 0; index < head_; index++) {
			Invalidate(index, decayModifier);
		}
	}

	return true;
}

