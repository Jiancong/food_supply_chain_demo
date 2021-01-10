#ifndef __KITCHEN_H__
#define __KITCHEN_H__
#include "Courier.h"
#include "Shelves.h"
#include "Order.h"
#include <memory>

using namespace std;

class Courier;

class Kitchen {
public:
	Kitchen();
	bool Init(string filepath);
	bool ProceedOrder(shared_ptr<Order> order, shared_ptr<Courier> courier);
	bool Run(int ingestCount);
	shared_ptr<Order> PickUpOrder(string orderId);

private:
	int orderSize_;
	string content_;
	unique_ptr<Shelves> shelves_;
	// current the cook operation is empty.
	bool Cook();
	bool AddOrder(shared_ptr<Order> order);

};

#endif
