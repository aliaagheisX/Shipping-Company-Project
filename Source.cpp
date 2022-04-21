#include <iostream>
#include<fstream>
#include "Company.h"
using namespace std;

void Simulate(Company& c)
{
	bool Cond1 = !(c.getEventList().isEmpty());
	bool Cond2 = !(c.getWaitingNormalCargo().isEmpty());
	bool Cond3 = !(c.getWaitingSpecialCargo().isEmpty());
	bool Cond4 = !(c.getWaitingVIPCargo().isEmpty());
	while (Cond1 || Cond2 || Cond3 || Cond4)
	{
		if (c.getCurrentTime() == c.getEventList().peekFront()->getEventTime())
		{

		}
	}
}

int main() {
	Company c;
	c.load();
	c.Print();


////* 1- Data members For All Classes
////! Company 
////Cargos - Truck - Time

////* 2- DSA ->
//// Linked List - Queue - Piority
////Test

//? 3 - UI CLass => two Modes
//// Load Function

////? 4 - Event CLass => Execute
//? 5 - Simple Simulator Function
	////? truck creation
	//? simulation function
	//? output
	////? promotion

	return 0;
}