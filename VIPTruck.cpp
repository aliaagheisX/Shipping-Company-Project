#include "VIPTruck.h"
int VIPTruck::CheckUPTime = 0;


VIPTruck::VIPTruck(ifstream& InFile) : Truck(InFile)
{
}

void VIPTruck::setCheckUPTime(const int& c) {
	CheckUPTime = c;
}

int VIPTruck::GetCheckUPTime() const
{
	return CheckUPTime;
}

// company =>