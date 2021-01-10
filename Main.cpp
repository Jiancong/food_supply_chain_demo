#include "Kitchen.h"
#include <iostream>

using namespace std;


int main(){

	cout << "************* Kitchen demo ************" << endl;
	cout << "Setup...." << endl;

	Kitchen* kitchen = new Kitchen();

	kitchen->Init("./orders.json");

	kitchen->Run(2);

	return 0;
}
