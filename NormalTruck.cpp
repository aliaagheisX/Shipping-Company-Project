#include "NormalTruck.h"
int NormalTruck::CheckUPTime = 0;



NormalTruck::NormalTruck(ifstream& InFile) : Truck(InFile)
{
}

void NormalTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}

int NormalTruck::GetCheckUPTime() const
{
	return CheckUPTime;
}
