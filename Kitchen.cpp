#include "Kitchen.h"
#include "util/cJSON.h"
#include "Courier.h"
#include <fstream>
#include <chrono>
#include <iostream>
#include "pthread.h"
#include <thread>

Kitchen::Kitchen() {
	shelves_ = new Shelves();
//	shelves_ = unique_ptr<Shelves>(new Shelves());
	//shelves_ = make_shared<Shelves>();
}

Kitchen::~Kitchen(){
	delete shelves_;
}

bool Kitchen::Init(string filepath) {

	cout << "----------- shelves_ address : " << shelves_ << ", kitchen address : " << this << endl;

	string jsonstring;
	ifstream jsonFile(filepath);

	while (getline(jsonFile, jsonstring)){
		content_ += jsonstring;
	}

	//cout << "content: " << content_ << endl;
	
	// Initialize and set thread joinable
	pthread_attr_init(&attr_);
	pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);

	return true;
}

bool Kitchen::AddOrder(shared_ptr<Order> order){

	return shelves_->AddOrder(order);
}

bool Kitchen::Run(int ingestCount) {



	if (ingestCount <= 0) return false;

	cJSON* root = cJSON_Parse(content_.c_str());
    if (root == NULL) {
		return false;
    } else {
    	orderSize_ = cJSON_GetArraySize(root);

		cout << "order size: " << orderSize_ << endl;

		// TBD flaw about ordersize assumption
		if (orderSize_ > kCourierNumber) {

			cerr << "invalid orderSize_" << endl;

			return false;
		}

        if (orderSize_ > 0) {

			for (int i = 0; i < orderSize_; i++){
				cJSON* item = cJSON_GetArrayItem(root, i);
				cJSON* idObject = cJSON_GetObjectItem(item, "id");
				cJSON* nameObject = cJSON_GetObjectItem(item, "name");
				cJSON* tempObject = cJSON_GetObjectItem(item, "temp");
				cJSON* shelfLifeObject = cJSON_GetObjectItem(item, "shelfLife");
				cJSON* decayRateObject = cJSON_GetObjectItem(item, "decayRate");

				string id = "";
				string name = "";
				string temp = "";
				double shelfLife = 0.0;
				double decayRate = 0.0;
				if (idObject != NULL) {
					id = idObject->valuestring;
				}

				if (nameObject != NULL) {
					name = nameObject->valuestring;
				}

				if (tempObject != NULL) {
					temp = tempObject->valuestring;
				}

				if (shelfLifeObject != NULL) {
					shelfLife = shelfLifeObject->valueint;
				}

				if (decayRateObject != NULL) {
					decayRate = decayRateObject->valuedouble;
				}

				cout << "id:[" << id << "], name:[" << name << "], temp:[" << temp << "], shelfLife:[" << shelfLife << "], decayRate:[" << decayRate<< "]"<< endl;

				shared_ptr<Order> order = make_shared<Order>(id, name, temp, shelfLife, decayRate);

				std::this_thread::sleep_for(std::chrono::milliseconds( 1000 / ingestCount ));

				//shared_ptr<Courier> courier = make_shared<Courier>(this);
				Courier *courier = new Courier(this);
				ProceedOrder(order, courier, i);
			}
			
        } else {
			cerr << "order size is invalid. quit..." << endl;
			cJSON_Delete(root);
			return false;
		}
        cJSON_Delete(root);

   		// free attribute and wait for the other threads
   		pthread_attr_destroy(&attr_);
		void* status;

		for(int i = 0; i < orderSize_; i++ ) {
			int rc = pthread_join(courierThreads_[i], &status);
			if (rc) {
				cerr << "Error:unable to join," << rc << endl;
				return false;
			}
			cout << "Main: completed thread id :" << i ;
			cout << "exiting with status :" << status << endl;
		}

		return true;
    }
}

bool Kitchen::ProceedOrder(shared_ptr<Order> order, Courier* courier, int i) {
	// Cook immediately.
	Cook();

	// Add order on shelf.
	AddOrder(order);

	courier->SetOrderId(order->GetId());

	//Courier* courierCopy = courier.get();
	Courier* courierCopy = courier;

	cout << "parent tid:" << pthread_self() << endl;

	pthread_create(&courierThreads_[i], &attr_, &Courier::thread_helper, (void *)courierCopy);

	cout << "son tid:" << courierThreads_[i]<< endl;


	cout << "Kitchen: order id: " << order->GetId() << " is processing." << endl;
}

bool Kitchen::Cook() {
	return true;
}

shared_ptr<Order> Kitchen::PickUpOrder(string orderid){

	cout << "Kitchen::PickUpOrder " << orderid << endl;

	cout << "current tid:" << pthread_self() << endl;

	cout << "----------- shelves_ address : " << shelves_ << ", kitchen address : " << this << endl;
	
	if (shelves_ == nullptr) {
		cerr << "shelves_ is unexpectly destroyed. This is fatal, exit." << endl;
		return nullptr;
	} else {
		return shelves_->Remove(orderid);
	}
}
