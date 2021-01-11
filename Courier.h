#ifndef __COURIER_H__
#define __COURIER_H__

#include <string>
#include <memory>
#include "Order.h"
#include "Kitchen.h"
#include <iostream>

using namespace std;

class Courier;

typedef struct thread_data {
	string orderId;
	shared_ptr<Order> result;
	shared_ptr<Courier> courier;
} thread_data;

class Kitchen;

class Courier {

private:
	long id_;
	static int kTotal_;
	Kitchen* kitchen_;
	string orderId_;

public:
	void SetOrderId(string orderid);
	string GetOrderId();

	//Courier();
	Courier(Kitchen* kit);

	~Courier();

	bool DeliverOrder(shared_ptr<Order> order); 

	void* PickUpOrder(void);
	static void* thread_helper(void* arg){
		cout << "thread_helper is running" << endl;
        Courier *c = (Courier*)arg;
		auto ret = ((Courier*)arg)->PickUpOrder();
        delete c;
        return ret;
	}
};

#endif
