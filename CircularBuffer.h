#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <mutex>
#include <memory>
#include "Order.h"

using namespace std;

class CircularBuffer {
public:
	explicit CircularBuffer(size_t size) :
		buf_(unique_ptr<shared_ptr<Order>[]>(new shared_ptr<Order>[size])),
		max_size_(size){};

	void Put(shared_ptr<Order> item);
	shared_ptr<Order> Get();
	void Reset();
	bool Empty() const;
	bool Full() const;
	size_t Capacity() const;
	size_t Size() const;
	bool Maintain(double decayModifier);
	void Invalidate(int index, double decayModifier);
	void SwapTail(int index); 
	shared_ptr<Order> Get(string id); 

	void PrintStatus();

private:
	mutex mutex_;
	unique_ptr<shared_ptr<Order>[]> buf_;
	size_t head_ = 0;
	size_t tail_ = 0;
	const size_t max_size_;
	bool full_ = 0;
};
#endif
