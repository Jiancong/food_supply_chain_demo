#include "Order.h"

Order::Order(string id, string name, string temp, double shelfLife, double decayRate){
	id_ = id;
	name_ = name;
	temp_ = temp;
	shelfLife_ = shelfLife;
	decayRate_ = decayRate;
	begin_ = chrono::steady_clock::now();
}

string Order::GetId(){
	return id_;
}

string Order::GetName(){
	return name_;
}

string Order::GetTemp(){
	return temp_;
}

double Order::GetShelfLife(){
	return shelfLife_;
}

double Order::GetDecayRate(){
	return decayRate_;
}

chrono::steady_clock::time_point Order::GetBegin(){
	return begin_;
}



