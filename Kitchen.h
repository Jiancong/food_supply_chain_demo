#ifndef __KITCHEN_H__
#define __KITCHEN_H__
#include "Courier.h"
#include "Shelves.h"
#include "Order.h"
#include <memory>

using namespace std;

class Courier;

const int kCourierNumber = 2000;

class Kitchen {
public:
	Kitchen();
	~Kitchen();
	bool Init(string filepath);
	bool ProceedOrder(shared_ptr<Order> order, Courier* courier, int index);
	bool Run(int ingestCount);
	shared_ptr<Order> PickUpOrder(string orderid);
	Shelves* shelves_;

private:
	int orderSize_;
	string content_;
	// current the cook operation is empty.
	bool Cook();
	bool AddOrder(shared_ptr<Order> order);
	pthread_attr_t attr_;
	pthread_t courierThreads_[kCourierNumber];

};

#endif
