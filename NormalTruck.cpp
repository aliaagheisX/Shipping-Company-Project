#include "NormalTruck.h"
#include "NormalCargo.h"
float NormalTruck::Speed = 0;
long NormalTruck::Capcity = 0;

NormalTruck::NormalTruck(long j) :Truck(Speed, Capcity)
{
	SetJ(j);
}

bool NormalTruck::AssignCargo(Cargo* c) {
	//TODO: 1- check if Queue not empty check Type
	//TODO: 2- if Empty -> VIP , Normal
	if (static_cast<NormalCargo*>(c))
		return true;
	return false;
}
