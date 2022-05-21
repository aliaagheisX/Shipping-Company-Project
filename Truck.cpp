#include "Truck.h"
int Truck::counter = 0;


Truck::Truck(float& s, int& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
	numberOfJourney = 0;
	tAT = 0;
	tDC = 0;
	totalJouneys = 0;
	MaxCargoDist = 0;
	NowMoving = false;
}

//////////////////////////////////////////////Getters
PriorityQueue<Cargo*> &  Truck::getCargoList()  {
	return loadedCargo;
}

int Truck::getNumberOfJourney() const {return numberOfJourney;}


Time Truck::GetDi() const{return DI;}

const Time& Truck::GetMt() const{return MT;}

float Truck::GetSpeed() const {return Speed;}

int Truck::GetCapcity() const {return Capcity;}
//////////////////////////////////////////////Getters

//////////////////////////////////////////////Setters
void Truck::SetMt(const Time& t){MT = t;}

void Truck::SetNumberOfJourney(int x){numberOfJourney = x;}

void Truck::setNowMoving(bool n) { NowMoving = n; }

void Truck::resetFinishingCheckUPTime()
{
	FinishingCheckUPTime.setDay(0);
	FinishingCheckUPTime.setHour(0);
}



Types Truck::getTypes() const {
/*
	if (dynamic_cast<NormalCargo*>(loadedCargo.peekFront())) return Normal;
	if (dynamic_cast<SpecialCargo*>(loadedCargo.peekFront())) return Special;
	if (dynamic_cast<VIPCargo*>(loadedCargo.peekFront())) return VIP;
*/
	return VIP;
}



//////////////////////////////////////////////DOs
bool Truck::AssignCargo(Cargo* c, const Time& currentTime)
{
	if (currentTime < FinishingLoadingTime) return false;

	c->setLoadingTruck(this);
	FinishingLoadingTime = currentTime + c->GetLt();
	loadedCargo.enqueue(c, (c->GetDist()));
	MaxCargoDist = (MaxCargoDist > c->GetDist()) ? MaxCargoDist : c->GetDist();
	DI = DI + c->GetLt();

	return true;
}
bool Truck::move(const Time* t)
{
	if (!NowMoving && Capcity > loadedCargo.getSize()) return false;
	if (*t < FinishingLoadingTime) return false;
	MT = *t;
	DI = DI + 2*(MaxCargoDist / Speed);
	numberOfJourney++;
	return true;		
}

void Truck::EndJourney() {
	tDC += Capcity;
	tAT += (DI + MT).ConvertToInt();
	totalJouneys++;

	NowMoving = false;
	MaxCargoDist = 0;
	MT.setDay(0);
	MT.setHour(0);
	DI.setDay(0);
	DI.setHour(0);
	FinishingLoadingTime.setDay(0);
	FinishingLoadingTime.setHour(0);
}

// Cargo char - simulate function - pormotion event - output - :priorityE