#include "UI.h"
#include"Cargo.h"
#include"Truck.h"
#include"Company.h"
#include<Windows.h>

UI::UI()
{
	int x;
	cout << "Choose Mode\n0 - interactive\n1 - Step By Step\n2 - Silent\nEnter Number : ";
	cin >> x;
	mode = Mode(x);
	cout << "\nSimulation Starts ...";
	Line();
}
void UI::InterActiveMode(Company* cPtr) {
	getchar();
	PrintScreen(cPtr);

}
void UI::StepByStepMode(Company* cPtr) {
	PrintScreen(cPtr);
	Sleep(1000);
}

int UI::Readmanual()
{
	int x;
	cout << "Enter Test Case Number: \n";
	cin >> x;
	return x;

}

void UI::Output(string s)
{
	if(mode != Silent)
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
	cout << Cptr->getLoadingTrucksCount() << " Loading Trucks: ";
	Cptr->getLoadingTrucks().Print(this, ' ');

	Line();
	 
	//							Empty Trucks:


	for (int Truck_Mode = DAY; Truck_Mode <= NIGHT; Truck_Mode++) {
		Output(to_string(Cptr->getEmptyTrucksCount()[Truck_Mode]) + " Empty " + (Truck_Mode ? "Night" : "Day") + " Trucks: ");
		for (int Truck_Type = Normal; Truck_Type <= VIP; Truck_Type++) {
			if (!Cptr->getEmptyTrucks(Truck_Mode)[Truck_Type].isEmpty()) {
				cout << open[Truck_Type];
				Cptr->getEmptyTrucks(Truck_Mode)[Truck_Type].Print(this);
				cout << close[Truck_Type];
			}
		}
		Line();
	}


	//							Moving Cargos:
	Output(to_string(Cptr->getMovingCargosCount()) + " Moving Cargos: ");
	
	Cptr->getMovingTrucks()->Print(this);
	Line();

	//							Check-up Trucks:
	for(int Truck_Mode = DAY; Truck_Mode <= NIGHT;Truck_Mode++){
		Output(to_string(Cptr->getMaintainingTrucksCount()[Truck_Mode]) + " In-Checkup " + (Truck_Mode ? "Night" : "Day") + " Trucks: ");
		for (int Truck_Type = Normal; Truck_Type <= VIP; Truck_Type++) {
			if (!Cptr->getMaintainingTrucks(Truck_Mode)[Truck_Type].isEmpty()) {
				cout << open[Truck_Type];
				Cptr->getMaintainingTrucks(Truck_Mode)[Truck_Type].Print(this);
				cout << close[Truck_Type];
			}
		}
		Line();
	}


	//							Delivered Cargos:
	Output(to_string(Cptr->getDeliveredCargosCount()) + " Delivered Cargos: ");

	for (int Truck_Type = Normal; Truck_Type <= VIP; Truck_Type++) {
		if (!Cptr->getDeliveredCargo()[Truck_Type].isEmpty()) {
			cout << open[Truck_Type];
			Cptr->getDeliveredCargo()[Truck_Type].Print(this);
			cout << close[Truck_Type];
		}
	}
	Line();

}


void UI::Print(Cargo* c, char seperator) { cout << to_string(c->getID()) << seperator; }
void UI::Print(Truck* t, char seprator) {
	if (!t) return;
	cout << to_string(t->getID());

	if (!t->getCargoList()->isEmpty()) {
		char open[3] = { '[', '(', '{' };
		char close[3] = { ']', ')', '}' };

		cout << open[t->getCargoType()];
		t->getCargoList()->Print(this, ',');
		cout  << close[t->getCargoType()] ;
	}
	cout << seprator;
}
void UI::Print(int n, char seperator)
{
	cout << n << seperator;
}
void UI::PlayMusic()
{
	if(mode != Silent)
		PlaySound(TEXT("WHY1.wav"), NULL, SND_FILENAME);
}
void UI::Print(Company* cPtr) {
	
	switch(mode)
	{
	case Interactive:
		InterActiveMode(cPtr);
		break;
	case StepByStep:
		StepByStepMode(cPtr);
		break;
	}
}

UI::~UI()
{
	cout << "\nSimulation ends, Output file created \n";
	Line();

}
