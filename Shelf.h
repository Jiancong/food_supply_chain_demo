#ifndef __SHELF_H__
#define __SHELF_H__

#include <CircularBuffer.h>
#include <Order.hpp>
#include <mutex>

using namespace std;

enum TEMPERATURE { HOT, COLD, FROZEN, OVERFLOW};

class Shelf {

private:
	TEMPERATURE temp_;
	double decayModifier_;
	int capacity_;
	unique_ptr<CircularBuffer<unique_ptr<Order> > > buffers_;

public:
	Shelf(TEMPERATURE t, int cap, double value);
	void SetTemp(TEMPERATURE temp);
	void SetCapacity(int cap);
	void SetDecayModifier(double value);

	bool Add(unique_ptr<Order> order);

	unique_ptr<Order> Remove();

	bool Full();

	TEMPERATURE GetTemp();
	int	GetCapacity();
	int GetSize();

	// 1 for single-temp, 2 for overflow shelf
	double GetDecayModifier();

};
#endif
