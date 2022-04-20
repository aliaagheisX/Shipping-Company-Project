#include "NormalTruck.h"
float NormalTruck::Speed = 0;
int NormalTruck::Capcity = 0;
int NormalTruck::CheckUPTime = 0;

NormalTruck::NormalTruck() :Truck(Speed, Capcity)
{
}

bool NormalTruck::AssignCargo(Cargo* c) {
	//TODO: 1- check if Queue not empty check Type
	//TODO: 2- if Empty -> VIP , Normal
	if (static_cast<Cargo*>(c))
		return true;
	return false;
}

void NormalTruck::SetSpeed(const float& s)
{
	Speed = s;
}
void NormalTruck::SetCapcity(const int& c)
{
	Capcity = c;
}

void NormalTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}