#include "Truck.h"
int Truck::counter = 0;


Truck ::Truck(float& s, int& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
}

Time Truck::GetDi() const
{
	return DI;
}



void Truck::SetMt(const Time& t)
{
	MT = t;
}

void Truck::SetDi(int x)
{
	DI = x;
}

void Truck::SetFDT(const Time& t)
{
	FinishingDeliveryTime = t;
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
Time Truck::GetFLT() const
{
	return FinishingDeliveryTime;
}
Time Truck::GetFDT() const
{
	return FinishingDeliveryTime;
}
bool Truck::move(const Time* t, bool now)
{
	if (!now && Capcity > loadedCargo.getSize()) return false;
	MT = *t;
	DI = DI + loadedCargo.peekFront()->GetDist() / Speed;
	return true;		
}
Types Truck::getTypes() const {
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

bool Truck::AssignCargo(Cargo* c, const Time& currentTime)
{
	if (currentTime < FinishingLoadingTime) return false;

	c->setLoadingTruck(this);
	FinishingLoadingTime = currentTime + c->GetLt();
	loadedCargo.enqueue(c, -1*(c->GetDist()));
	DI = DI + c->GetLt();

	return true;
}


// Cargo char - simulate function - pormotion event - output - :priorityE