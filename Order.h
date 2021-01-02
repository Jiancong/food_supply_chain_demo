#ifndef __ORDER_H__
#define __ORDER_H__
#include <chrono>

class Order{
private:
	String id;
	String name;
	String temp;
	int shelfLife;
	double decayRate;
	chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	double value;

public:
	Order(	String id,
			String name, 
			String temp, 
			int shelfLife,
			double decayRate);

	String GetId();
	String GetName();
	String GetTemp();
	int	GetShelfLife();
	double GetDecayRate();
	double GetValue();

	void SetId(String id);
	void SetName(String name);
	void SetTemp(String temp);
	void SetShelfLife(int shelfLife);
	void SetDecayRate(double decayRate);
};
#endif
