#ifndef __ORDER_H__
#define __ORDER_H__
#include <chrono>

class Order{
private:
	String id_;
	String name_;
	String temp_;
	double shelfLife_;
	double decayRate_;
	chrono::steady_clock::time_point begin_;

public:
	Order(	String id,
			String name, 
			String temp, 
			double shelfLife,
			double decayRate);

	String GetId();
	String GetName();
	String GetTemp();
	double GetShelfLife();
	double GetDecayRate();
	time_point GetBegin();

	/*
	void SetId(String id);
	void SetName(String name);
	void SetTemp(String temp);
	void SetShelfLife(double shelfLife);
	void SetDecayRate(double decayRate);
	*/
};
#endif
