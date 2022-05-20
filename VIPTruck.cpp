#include "VIPTruck.h"
float VIPTruck::Speed = 0;
int VIPTruck::Capcity = 0;
int VIPTruck::CheckUPTime = 0;

VIPTruck::VIPTruck() :Truck( Speed, Capcity)
{
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