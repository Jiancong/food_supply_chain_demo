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
	unordered_map<string, shared_ptr<Shelf>> shelves_;
	shared_ptr<Shelf> overflowShelf_;

	// accelarate orderId to shelf mapping.
	unordered_map<string, string> shelfMapper_;

	void processOverflow(shared_ptr<Order> order);

public:
	static string ToUpper(string str) {
		for (auto & c: str) c = toupper(c);
		return str;
	}

	Shelves();
	bool AddOrder(shared_ptr<Order> order);
	shared_ptr<Order> Remove(string orderId);
	void Maintain();
};
#endif
