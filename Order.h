#ifndef __ORDER_H__
#define __ORDER_H__
#include <chrono>
#include <string>
using namespace std;

class Order{
private:
	string id_;
	string name_;
	string temp_;
	double shelfLife_;
	double decayRate_;
	chrono::steady_clock::time_point begin_;

public:
	Order(	string id,
			string name, 
			string temp, 
			double shelfLife,
			double decayRate);

	string GetId();
	string GetName();
	string GetTemp();
	double GetShelfLife();
	double GetDecayRate();
	chrono::steady_clock::time_point GetBegin();

	/*
	void SetId(string id);
	void SetName(string name);
	void SetTemp(string temp);
	void SetShelfLife(double shelfLife);
	void SetDecayRate(double decayRate);
	*/
};
#endif
