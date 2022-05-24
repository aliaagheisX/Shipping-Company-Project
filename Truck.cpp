#include "Truck.h"
int Truck::counter = 0;


void Truck::Failuer(const Time* t, UI * uiPtr)
{
	srand(time(0));
	if (rand() % 100 >0 || isFailed) return;

	uiPtr->Output("Failure Happen : " + to_string(ID) + " is Failed and need maintaince.\n");
	isFailed = true;

	PriorityQueue<Cargo*>* aux = new PriorityQueue<Cargo*>(Capcity);
	int distance = getCargoList()->peekFront()->GetDist();
	int prev = 0;
	while (!getCargoList()->isEmpty())
	{
		Cargo* c = getCargoList()->peekFront();
		prev += c->GetLt();
		getCargoList()->dequeue();
		c->setCDT(*t + ceil(distance / Speed) + prev);

		aux->enqueue(c,c->getCDT().ConvertToInt());
	}
	delete loadedCargo;
	loadedCargo = aux;
	MT = *t;
	DI.setHour(ceil(distance / Speed) + prev);
}

Types Truck::getTypes() const
{
		if (loadedCargo->isEmpty()) return getTruckType();
		return (Types)loadedCargo->peekFront()->getType();
}

Truck::Truck(float& s, int& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
	numberOfJourney = 0;
	tAT = 0;
	tDC = 0;
	totalJouneys = 0;
	NowMoving = false;
	isFailed = false;
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
	return (double)tDC / (Capcity * totalJouneys) * ((double)tAT / Tsim.ConvertToInt());
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
		//handeling
		c->SetWt( Time(0, MT.ConvertToInt() - c->GetPt().ConvertToInt()) );

		prevLoadingTime += c->GetLt();
		
		c->setCDT(MT + ceil(c->GetDist() / Speed) + prevLoadingTime);
		aux->enqueue(c, c->getCDT().ConvertToInt());
		
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

/**
 * @brief 
 * Checkup => bool
 * setFinishCheckUP
 * 
*/

bool Truck::CheckUP(const Time & currentTime, int J) {
	if (isFailed || numberOfJourney >= J) {
		FinishingCheckUPTime = currentTime + GetCheckUPTime();
		return true;
	}
	return false;
}
 bool Truck::isFinishedCheckUp(const Time& currentTime) const { return ( FinishingCheckUPTime <=currentTime ); }

void Truck::endCheckUp()
{
	numberOfJourney = 0;
	isFailed = false;
	FinishingCheckUPTime.setDay(0);
	FinishingCheckUPTime.setHour(0);
}


Truck::~Truck() {
	delete loadedCargo;
}
// Cargo char - simulate function - pormotion event - output - :priorityE

//TAt = Assign, 