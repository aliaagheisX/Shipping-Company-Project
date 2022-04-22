#include "UI.h"
#include"Cargo.h"
#include"Truck.h"
#include"Company.h"
#include<Windows.h>

void UI::ReadMode() {
	int x;
	cout << "Choose Mode\n0 - interactive\n1 - Step By Step\n2 - Silent\nEnter Number : ";
	cin >> x;
	mode = Mode(x);
}
void UI::InterActiveMode(Company* cPtr) {
	getchar();
	PrintScreen(cPtr);

}
void UI::StepByStepMode(Company* cPtr) {
	PrintScreen(cPtr);
	Sleep(1000);
}

void UI::Output(string s)
{
	cout << s;
}

void UI::Line()
{
	cout << "\n";

	for (int i = 0; i < 50; i++)
	{
		cout << "-";
	}
	cout << "\n";
}


void UI::PrintScreen(Company* Cptr) {
	Line();

	char open[3] = { '[', '(', '{' };
	char close[3] = { ']', ')', '}' };
	cout << "Current Time (Day:Hour):";
	Cptr->getCurrentTime().Print(this);
	cout << '\n';

	//							Waiting Cargos:
	Output(to_string(Cptr->getWaitingCargosCount()) + " Waiting Cargos: ");
	if (Cptr->getWaitingNormalCargo().getSize() != 0){
		cout << '[';
		Cptr->getWaitingNormalCargo().Print(this);
		cout << "] ";
	}
	if(Cptr->getWaitingSpecialCargo().getSize() != 0) {
		cout << '(';
		Cptr->getWaitingSpecialCargo().Print(this);
		cout << ") ";
	}
	if (Cptr->getWaitingVIPCargo().getSize() != 0) {
		cout << '{';
		Cptr->getWaitingVIPCargo().Print(this);
		cout << "} ";
	}
	Line();
	//							Loading Trucks:
	Output("0 Loading Trucks: ");

	Line();
	 
	//							Empty Trucks:

	Output(to_string(Cptr->getEmptyTrucksCount()) + " Empty Trucks: ");

	if (Cptr->getEmptyTrucks()[Normal].getSize() != 0) {
		cout << '[';
		Cptr->getEmptyTrucks()[Normal].Print(this);
		cout << "] ";
	}
	if (Cptr->getEmptyTrucks()[Special].getSize() != 0) {
		cout << '(';
		Cptr->getEmptyTrucks()[Special].Print(this);
		cout << ") ";
	}
	if (Cptr->getEmptyTrucks()[VIP].getSize() != 0) {
		cout << '{';
		Cptr->getEmptyTrucks()[VIP].Print(this);
		cout << "} ";
	}
	Line();
	//							Moving Cargos:
	Output(to_string(Cptr->getMovingCargosCount()) + " Moving Cargos: ");
	Cptr->getMovingTrucks().Print(this);
	Line();
	//							Check-up Cargos:
	Output(to_string(Cptr->getMaintainingTrucksCount()) + " In-Checkup Trucks: ");
	if (Cptr->getMaintainingTrucks()[Normal].getSize() != 0) {
		cout << '[';
		Cptr->getMaintainingTrucks()[Normal].Print(this);
		cout << "] ";
	}
	if (Cptr->getMaintainingTrucks()[Special].getSize() != 0) {
		cout << '(';
		Cptr->getMaintainingTrucks()[Special].Print(this);
		cout << ") ";
	}
	if (Cptr->getMaintainingTrucks()[VIP].getSize() != 0) {
		cout << '{';
		Cptr->getMaintainingTrucks()[VIP].Print(this);
		cout << "} ";
	}
	Line();


	//							Delivered Cargos:
	Output(to_string(Cptr->getDeliveredCargosCount()) + " Delivered Cargos: ");
	if (Cptr->getDeliveredCargo()[Normal].getSize() != 0) {
		cout << '[';
		Cptr->getDeliveredCargo()[Normal].Print(this);
		cout << "] ";
	}
	if (Cptr->getDeliveredCargo()[Special].getSize() != 0) {
		cout << '(';
		Cptr->getDeliveredCargo()[Special].Print(this);
		cout << ") ";
	}
	if (Cptr->getDeliveredCargo()[VIP].getSize() != 0) {
		cout << '{';
		Cptr->getDeliveredCargo()[VIP].Print(this);
		cout << "} ";
	}
	Line();

}


void UI::Print(Cargo* c) { cout << to_string(c->getID()); }
void UI::Print(Truck* t) { 

	cout << to_string(t->getID());

	if (!t->getCargoList().isEmpty()) {
		char open[3] = { '[', '(', '{' };
		char close[3] = { ']', ')', '}' };

		cout << open[t->getCargoType()];
		t->getCargoList().Print(this);
		cout  << close[t->getCargoType()] << " ";
	}
}
void UI::Print(Company* cPtr) {
	switch (mode)
	{
	case Interactive:
		InterActiveMode(cPtr);
		break;
	case StepByStep:
		StepByStepMode(cPtr);
		break;
	default:
		InterActiveMode(cPtr);
		break;
	}
}
