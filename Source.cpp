#include <iostream>
#include "LinkedList.h"
using namespace std;
int main() {
	LinkedList<int> q;

	q.addFront(3);
	q.addFront(2);
	q.addFront(1);
	q.addBack(4);
	q.addBack(5);
	q.Insert(0, 0);
	q.Insert(0, 6);
	try {
		q.Insert(30, 10);
	}
	catch (exception e) {
		cout << e.what() << '\n';
	}

	auto it = q.getIterator();

	while (it) {
		cout << it->getValue() << ' ';
		it = it->getNext();
	}
	cout << '\n';
	q.removeFront();
	q.removeFront();
	q.removeBack();

	it = q.getIterator();

	while (it) {
		cout << it->getValue() << ' ';
		it = it->getNext();
	}
	cout << '\n';



	q.removeIndex(2);
	q.removeValue(5);

	it = q.getIterator();

	while (it) {
		cout << it->getValue() << ' ';
		it = it->getNext();
	}

//* 1- Data members For All Classes
//! Company 
////Cargos - Truck - Time

//* 2- DSA ->
//// Linked List - Queue - Piority
////Test
//! CargoList - TruckList

//? 3 - UI CLass
//! Load Function

//? 4 - Event CLass
//? 5 - Simple Simulator Function
	return 0;
}