#include "Order.h"

Order::Order(String id, String name, String temp, double shelfLife, double decayRate){
	id_ = id;
	name_ = name;
	temp_ = temp;
	shelfLife_ = shelfLife;
	decayRate_ = decayRate;
	begin_ = chrono::steady_clock::now();
}

String Order::GetId(){
	return id_;
}

String Order::GetName(){
	return name_;
}

String Order::GetTemp(){
	return temp_;
}

double Order::GetShelfLife(){
	return shelfLife_;
}

double Order::GetDecayRate(){
	return decayRate_;
}

time_point Order::GetBegin(){
	return begin_;
}



