#ifndef __COURIER_H__
#define __COURIER_H__

#include <string>
#include <memory>
#include "Order.h"
#include "Kitchen.h"

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
	Courier(Kitchen* kit){
		id_ = kTotal_ ;
		kTotal_++;
		kitchen_ = kit;
	}

	void* PickUpOrder(void* arg);
	static void* thread_helper(void* arg){
		return (((thread_data*)arg)->courier)->PickUpOrder(arg);
	}
};

#endif
