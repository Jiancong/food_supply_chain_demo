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
	//Set<unique_ptr<Order> > buffers_;
	//Set<unique_ptr<Order> >::iterator it_;
	//mutex	mutex_;
	CircularBuffer<unique_ptr<Order> > buffers_;

public:
	Shelf(TEMPERATURE t, int cap, double value);
	void SetTemp(TEMPERATURE temp);
	void SetCapacity(int cap);
	void SetDecayModifier(double value);

	bool Add(unique_ptr<Order> order);

	// 'false' means remove element failed 
	bool Remove();

	bool Full();

	TEMPERATURE GetTemp();
	int	GetCapacity();
	int GetSize();

	// 1 for single-temp, 2 for overflow shelf
	double GetDecayModifier();

	

};
#endif
