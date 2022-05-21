#include "NormalTruck.h"
float NormalTruck::Speed = 0;
int NormalTruck::Capcity = 0;
int NormalTruck::CheckUPTime = 0;

NormalTruck::NormalTruck() :Truck(Speed, Capcity)
{
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

int NormalTruck::GetCheckUPTime() const
{
	return CheckUPTime;
}
