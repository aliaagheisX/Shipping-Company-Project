#include "VIPTruck.h"
float VIPTruck::Speed = 0;
int VIPTruck::Capcity = 0;
int VIPTruck::CheckUPTime = 0;

VIPTruck::VIPTruck() :Truck( Speed, Capcity)
{
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

void VIPTruck::SetCapcity(const int& c)
{
	Capcity = c;
}
void VIPTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}

// company =>