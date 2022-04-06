#include "SpecialTruck.h"
#include "SpecialCargo.h"
float SpecialTruck::Speed = 0;
long SpecialTruck::Capcity = 0;

SpecialTruck::SpecialTruck(long j) :Truck(Speed, Capcity)
{
	SetJ(j);
}

bool SpecialTruck::AssignCargo(Cargo* c) {

	if (dynamic_cast<SpecialCargo*>(c)){
		loadedCargo.enqueue(c);
		return true;
	}
	return false;
}

void SpecialTruck::SetSpeed(const float& s)
{
	Speed = s;
}


void SpecialTruck::SetCapcity(const long& c)
{
	Capcity = c;
}

void SpecialTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}