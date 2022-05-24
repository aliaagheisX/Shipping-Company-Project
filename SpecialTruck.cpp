#include "SpecialTruck.h"
int SpecialTruck::CheckUPTime = 0;


SpecialTruck::SpecialTruck(ifstream& InFile) : Truck(InFile)
{
}

void SpecialTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}

int SpecialTruck::GetCheckUPTime() const
{
	return CheckUPTime;
}
