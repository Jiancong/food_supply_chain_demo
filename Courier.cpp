#include "Courier.h"
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

/*
static void* Courier::thread_helper(void* arg){
	return (((thread_data*)arg)->courier)->PickUpOrder(arg);
}*/

int Courier::kTotal_ = 0;

/*
Courier::Courier(){
	id_ = kTotal_;
	kTotal_++;
	kitchen_ = nullptr;
}*/

/*
Courier::Courier(Kitchen_* kit){
	id_ = kTotal_ ;
	kTotal_++;
	kitchen_ = kit;
}*/

void* Courier::PickUpOrder(void* arg){

	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(2, 6); // define the range
	int seconds = distr(gen); 

	thread_data* tdata=(thread_data*)arg;

	if (tdata == nullptr) {
		cout << "received invalid pointer." << endl;
		return nullptr;
	} else {
		cout << "received valid pointer." << endl;
	}

	string id=tdata->orderId;

	// sleep randamly
	std::this_thread::sleep_for(std::chrono::seconds(seconds));

	shared_ptr<Order> order = kitchen_->PickUpOrder(id);

	tdata->result=order;

	pthread_exit(NULL);
}

void Courier::SetOrderId(string orderid){
	orderId_ = orderid;
}

string Courier::GetOrderId(){
	return orderId_;
}


