#include "Courier.h"
#include <random>
#include <chrono>
#include <thread>

/*
static void* Courier::thread_helper(void* arg){
	return (((thread_data*)arg)->courier)->PickUpOrder(arg);
}*/

int Courier::kTotal_ = 0;

Courier::Courier(Kitchen* kit){
	id_ = kTotal_ ;
	kTotal_++;
	kitchen_ = kit;

	cout << "------------- Courier : " << id_ << ", kitchen address: " << kitchen_ << ", shelves address:" << kitchen_->shelves_ << endl;
}

Courier::~Courier(){
	cout << "courier [" << id_ << "] is destroyed." << endl;
	cout << "pre destroyed the address of shelves is " << kitchen_->shelves_ << endl;
	kitchen_ = nullptr;
}

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

void* Courier::PickUpOrder(void){

	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(2, 6); // define the range
	int seconds = distr(gen); 

	// sleep randamly
	std::this_thread::sleep_for(std::chrono::seconds(seconds));

	kitchen_->PickUpOrder(orderId_);

	pthread_exit(NULL);
}

bool Courier::DeliverOrder(shared_ptr<Order> order) {

	cout << "Courier:" << id_ << " deliver order: " << order->GetId() << endl;

	return true;
}

void Courier::SetOrderId(string orderid){
	orderId_ = orderid;
}

string Courier::GetOrderId(){
	return orderId_;
}


