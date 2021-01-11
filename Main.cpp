#include "Kitchen.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[]){

	int k = 2;
	if (argc != 2) {
		cerr << "Usage:" << endl;
		cerr << "\t./Kitchen <ingest count per second>" << endl;
		return -1;
	} else {
		k = atoi(argv[1]);
		if (k < 0 || k > 100) {
			cerr << "please input valid ingest count." << endl;
			return -1;
		}
	}

	cout << "************* Kitchen demo ************" << endl;
	cout << "setup k:" << k << endl;

	Kitchen* kitchen = new Kitchen();

	kitchen->Init("./orders.json");

	kitchen->Run(k);

	return 0;
}
