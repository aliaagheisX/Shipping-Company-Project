#include "Truck.h"
int Truck::counter = 0;


Truck ::Truck(float& s, int& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
}

int Truck::GetDi() const
{
	//! calculate Deleviery interval
	return DI;
}


void Truck::SetMt(const Time& t)
{
	MT = t;
}

const Time& Truck::GetMt() const
{
	return MT;
}

float Truck::GetSpeed() const
{
	return Speed;
}

int Truck::GetCapcity() const
{
	return Capcity;
}
CargoType Truck::getCargoType() const {
/*
	if (dynamic_cast<NormalCargo*>(loadedCargo.peekFront())) return Normal;
	if (dynamic_cast<SpecialCargo*>(loadedCargo.peekFront())) return Special;
	if (dynamic_cast<VIPCargo*>(loadedCargo.peekFront())) return VIP;
*/
	return VIP;
}

PriorityQueue<Cargo*> &  Truck::getCargoList()  {
	return loadedCargo;
}


// Cargo char - simulate function - pormotion event - output - :priorityE