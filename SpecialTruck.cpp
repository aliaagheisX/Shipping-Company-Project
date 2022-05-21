#include "SpecialTruck.h"
float SpecialTruck::Speed = 0;
int SpecialTruck::Capcity = 0;
int SpecialTruck::CheckUPTime = 0;

SpecialTruck::SpecialTruck() :Truck(Speed, Capcity)
{
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

int SpecialTruck::GetCheckUPTime() const
{
	return CheckUPTime;
}
