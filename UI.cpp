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
	cout << "Current Time (Day:Hour):" << Cptr->getCurrentTime().TimePrint() << '\n';

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
	int count = 0;
	for (int i = 0; i < Cptr->getLoadingTrucks().getSize(); i++) 
		if(Cptr->getLoadingTrucks().getEntry(i))
			count++;
	cout << count << " Loading Trucks: ";
	if (Cptr->getLoadingTrucks().getEntry(Normal)) {
		cout << '[';
		Cptr->getLoadingTrucks().getEntry(Normal)->getCargoList().Print(this);
		cout << ']';
	}
	if (Cptr->getLoadingTrucks().getEntry(Special)) {
		cout << '(';
		Cptr->getLoadingTrucks().getEntry(Special)->getCargoList().Print(this);
		cout << ')';
	}
	if (Cptr->getLoadingTrucks().getEntry(VIP)) {
		cout << '{';
		Cptr->getLoadingTrucks().getEntry(VIP)->getCargoList().Print(this);
		cout << '}';
	}
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
	Cptr->getDeliveredCargo().Print(this);
	Line();

}


void UI::Print(Cargo* c) { cout << to_string(c->getID()); }
void UI::Print(Truck* t) { 

	cout << to_string(t->getID());

	if (!t->getCargoList().isEmpty()) {
		char open[3] = { '[', '(', '{' };
		char close[3] = { ']', ')', '}' };

		cout << open[t->getTypes()];
		t->getCargoList().Print(this);
		cout  << close[t->getTypes()] << " ";
	}
}
void UI::Print(int n)
{
	cout << n;
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
