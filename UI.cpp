#include "UI.h"
#include"Cargo.h"
#include"Truck.h"
#include"Company.h"

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


void UI::PrintData(Company* Cptr) {

}


void UI::Print(Cargo* c) { cout << to_string(c->getID()); }
void UI::Print(Truck* t) { cout << to_string(t->getID()); }