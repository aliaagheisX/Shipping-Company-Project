#include <iostream>
#include<fstream>
#include"Time.h"
#include "LinkedList.h"
using namespace std;
int main() {
	Time T;
	
	ifstream file;
	file.open("Timee.txt");
	T.Read(file);
	cout << T.getDay() << " " << T.getHour();
	// 
//* 1- Data members For All Classes
//! Company 
////Cargos - Truck - Time

//* 2- DSA ->
//// Linked List - Queue - Piority
////Test

//? 3 - UI CLass => two Modes
//// Load Function

//? 4 - Event CLass => Execute
//? 5 - Simple Simulator Function
	//? truck creation

	return 0;
}