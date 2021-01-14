#ifndef __KITCHEN_H__
#define __KITCHEN_H__
#include "Courier.h"
#include "Shelves.h"
#include "Order.h"
#include <memory>
#include "util/ThreadPool.h"

using namespace std;

class Courier;

class Kitchen {
public:
	Kitchen();
	Kitchen(int courierNum);
	virtual ~Kitchen();
	bool Init(string filepath);
	bool ProceedOrder(shared_ptr<Order> order, Courier* courier, int index);
	bool Run(int ingestCount);
	shared_ptr<Order> PickUpOrder(string orderid);
	Shelves* shelves_;

private:
	int orderSize_;
	string content_;
	int courierNum_;

	// current the cook operation is empty.
	bool Cook();
	bool AddOrder(shared_ptr<Order> order);

	ThreadPool* threadPool_;
	vector< future<string> > results_;

};

#endif
