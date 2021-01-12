#ifndef __SHELVES_H__
#define __SHELVES_H__

#include <list>
#include <string>
#include "Shelf.h"
#include "Order.h"
#include <unordered_map>

using namespace std;

class Shelves {

private:
	// composite single shelf
	unordered_map<string, shared_ptr<Shelf>> shelvesMap_;
	shared_ptr<Shelf> overflowShelf_;

	void ProcessOverflow(shared_ptr<Order> order);

public:
	bool PrintStatus();
	static string ToUpper(string str) {
		for (auto & c: str) c = toupper(c);
		return str;
	}

	Shelves();
	Shelves(int coldSize, int frozenSize, int hotSize, int overflowSize);
	bool AddOrder(shared_ptr<Order> order);
	shared_ptr<Order> Remove(string orderId);
	void Maintain();
	shared_ptr<Shelf> GetShelf(string temp);
};
#endif
