#include "SpecialTruck.h"
float SpecialTruck::Speed = 0;
int SpecialTruck::Capcity = 0;
int SpecialTruck::CheckUPTime = 0;

SpecialTruck::SpecialTruck() :Truck(Speed, Capcity)
{
}

bool SpecialTruck::AssignCargo(Cargo* c) {

	if (c->getType() == 'S')
	{
		getCargoList().enqueue(c, c->GetDist());
		return true;
	}
	else if (c->getType() == 'V')
	{
		getCargoList().enqueue(c, - (c->getPriority()));
		return true;
	}
	return false;
}

void SpecialTruck::SetSpeed(const float& s)
{
	Speed = s;
}


void SpecialTruck::SetCapcity(const int& c)
{
	Capcity = c;
}

void SpecialTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}