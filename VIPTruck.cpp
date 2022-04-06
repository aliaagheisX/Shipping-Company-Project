#include "VIPTruck.h"
#include "VIPCargo.h"
float VIPTruck::Speed = 0;
long VIPTruck::Capcity = 0;

VIPTruck::VIPTruck(long j) :Truck( Speed, Capcity)
{
	SetJ(j);
}
bool VIPTruck::AssignCargo(Cargo* c) {
	//TODO: 1- check if Queue not empty check Type
	//TODO: 2- if Empty -> VIP , Normal
	return false;
}

void VIPTruck::SetSpeed(const float& s)
{
	Speed = s;
}

void VIPTruck::SetCapcity(const long& c)
{
	Capcity = c;
}
void VIPTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}

// company =>