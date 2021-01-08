#include "Kitchen.h"
#include "util/cJSON.h"
#include "Courier.h"
#include <fstream>
#include <chrono>
#include "pthread.h"
#include <thread>

Kitchen::Kitchen() {
	shelves_ = unique_ptr<Shelves>(new Shelves());
	Init("./orders.json");
}

bool Kitchen::Init(string filepath) {

	string jsonstring;
	ifstream jsonFile(filepath);

	while (getline(jsonFile, jsonstring)){
		content_ += jsonstring;
	}

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

				shared_ptr<Order> order = make_shared<Order>(id, name, temp, shelfLife, decayRate);

				std::this_thread::sleep_for(std::chrono::milliseconds( 1000 / ingestCount ));

				shared_ptr<Courier> courier = make_shared<Courier>(this);
				ProcessOrder(order, courier);
			}
			
        }
        cJSON_Delete(root);
    }
}

bool Kitchen::ProcessOrder(shared_ptr<Order> order, shared_ptr<Courier> courier) {
	// Cook immediately.
	Cook();

	// Add order on shelf.
	AddOrder(order);

	// call courier to pick up
	pthread_t tid;
	thread_data tdata;
	tdata.orderId = order->GetId();
	tdata.courier = courier;

	pthread_create(&tid, nullptr, &Courier::thread_helper, (void *)&tdata);

	pthread_join(tid, nullptr);

	if (tdata.result != nullptr){
		return true;
	} else {
		return false;
	}
}

shared_ptr<Order> Kitchen::PickUpOrder(string orderId) {
	return shelves_->Remove(orderId);
}

bool Kitchen::Cook() {
	// do nothing.
	return true;
}
