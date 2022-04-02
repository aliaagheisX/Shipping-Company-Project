#include "VIPTruck.h"
#include "VIPCargo.h"
Time VIPTruck::MT = Time();
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
