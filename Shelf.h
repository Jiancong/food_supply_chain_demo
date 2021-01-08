#ifndef __SHELF_H__
#define __SHELF_H__

#include "CircularBuffer.h"
#include "Order.h"
#include <mutex>

using namespace std;

class Shelf {

private:
	string temp_;
	double decayModifier_;
	int capacity_;
	unique_ptr<CircularBuffer> buffers_;

public:
	Shelf(string temp, double decayModifier, int capacity);
	void SetTemp(string temp);
	void SetCapacity(int cap);
	void SetDecayModifier(double value);

	bool Add(shared_ptr<Order> order);

	shared_ptr<Order> Remove(string orderId);
	shared_ptr<Order> Remove();

	shared_ptr<Order> Find(string orderId);

	bool Full();

	string GetTemp();
	int	GetCapacity();
	int GetSize();
	void Maintain();

	// 1 for single-temp, 2 for overflow shelf
	double GetDecayModifier();
};
#endif
