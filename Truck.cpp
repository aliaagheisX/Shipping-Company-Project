#include "Truck.h"
int Truck::counter = 0;


Truck::Truck(float& s, int& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
	numberOfJourney = 0;
	tAT = 0;
	tDC = 0;
	totalJouneys = 0;
	NowMoving = false;
	MaxCargoDist = 0;
	loadedCargo = new PriorityQueue<Cargo*>(Capcity);
}

//////////////////////////////////////////////Getters
PriorityQueue<Cargo*> *  Truck::getCargoList()  {
	return loadedCargo;
}

int Truck::getTotalActiveTime() const{return tAT;}

double Truck::getTruckUtilization(const Time& Tsim)
{
	if (!totalJouneys) return 0;
	return ((double)tDC / Capcity * totalJouneys) * ((double)tAT / Tsim.ConvertToInt());
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


//////////////////////////////////////////////DOs
bool Truck::AssignCargo(Cargo* c, const Time& currentTime)
{
	tAT++;
	if (currentTime < FinishingLoadingTime) return false;

	c->setLoadingTruck(this);

	FinishingLoadingTime = currentTime + c->GetLt();
	loadedCargo->enqueue(c, (c->GetDist()));
	MaxCargoDist = MaxCargoDist > c->GetDist() ? MaxCargoDist : c->GetDist();
	return true;
}
bool Truck::move(const Time* t)
{

	if (!NowMoving && Capcity > loadedCargo->getSize() || *t < FinishingLoadingTime) return false;
	MT = *t;

	//////////////////////////Set WT, CDT for Cargos
	int prevLoadingTime = 0;
	
	PriorityQueue<Cargo*>* aux = new PriorityQueue<Cargo*>(Capcity); //cargos that assigned on truck
	while (!loadedCargo->isEmpty()) {
		//handeling
		Cargo* c = loadedCargo->peekFront();
		loadedCargo->dequeue();
		aux->enqueue(c, c->GetDist());
		//handeling
		c->SetWt( Time(0, MT.ConvertToInt() - c->GetPt().ConvertToInt()) );

		prevLoadingTime += c->GetLt();
		
		c->setCDT(MT + ceil(c->GetDist() / Speed) + prevLoadingTime);

		
	}
	DI.setHour(prevLoadingTime + 2 * (MaxCargoDist / Speed));
	//handeling
	delete loadedCargo;
	loadedCargo = aux;
	//////////////////////////Set WT, CDT for Cargos
	return true;		
}
Cargo* Truck::DeliverCargos(const Time& currentTime)
{
	if (loadedCargo->isEmpty()) return NULL;
	tAT++;
	if (loadedCargo->peekFront()->getCDT() <= currentTime) {
		Cargo* c = loadedCargo->peekFront();
		tDC++;
		loadedCargo->dequeue();
		return c;
	}
	return NULL;
}



void Truck::EndJourney() {
	numberOfJourney++;
	totalJouneys++;
	MaxCargoDist = 0;
	NowMoving = false;
	MT.setDay(0);
	MT.setHour(0);
	DI.setDay(0);
	DI.setHour(0);
	FinishingLoadingTime.setDay(0);
	FinishingLoadingTime.setHour(0);
}


void Truck::endCheckUp()
{
	numberOfJourney = 0;
	FinishingCheckUPTime.setDay(0);
	FinishingCheckUPTime.setHour(0);
}


bool Truck::getFailure() const{
	srand(time(0));
	return (rand() % 100 < 5);
}

Truck::~Truck() {
	delete loadedCargo;
}
// Cargo char - simulate function - pormotion event - output - :priorityE

//TAt = Assign, 