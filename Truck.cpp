#include "Truck.h"
int Truck::counter = 0;

Truck::Truck(ifstream & InFile): ID(counter + 1)
{
	counter++; // for ID
	Read(InFile); // read the speed , capacity, isNightShift

	NowMoving = false;
	isFailed = false;
	numberOfJourney = 0;
	totalJouneys = 0;
	MaxCargoDist = 0;
	tAT = 0;
	tDC = 0;
	loadedCargo = new PriorityQueue<Cargo*>(Capcity); //set Capacity of heap array to Truck Capcity 
													  // as it max size can reach
}

void Truck::Read(ifstream& InFile)
{
	InFile >> Speed >> Capcity >> isNightShift;
}

/////Getters of Properties Of Truck
int Truck::GetCapcity() const {return Capcity;}
int Truck::getID() const { return ID; }
bool Truck::getIsNightShift() const { return isNightShift; }
int Truck::getPriority() const { return -1 * (0.5 * Speed + 8 * Capcity); }

///getters of truck properties in journey
//calculated Times
const Time& Truck::GetDi() const{return DI;}
const Time& Truck::GetMt() const{return MT;}
//Cargos properties or list in Truck
Types Truck::getCargoType() const
{
	//handeling if no cargo loaded or assigned return truck type
	if (loadedCargo->isEmpty()) return getTruckType();

	return (Types)loadedCargo->peekFront()->getType();
}
const PriorityQueue<Cargo*> *  Truck::getCargoList() const   {
	return loadedCargo;
}


//getters for statistice 
int Truck::getTotalActiveTime() const{return tAT;}
double Truck::getTruckUtilization(const Time& Tsim) const
{
	if (!totalJouneys) return 0;
	return (double)tDC / (Capcity * totalJouneys) * ((double)tAT / Tsim.ConvertToInt());
}
 

//Setters of Truck
void Truck::setNowMoving(bool n) { NowMoving = n; }
void Truck::SetSpeed(const float s){Speed = s;}


///DOs of Truck

/**
 * @brief 
 * Truck Responsible for
 *	1-Assign Cargo To itself
 *	2-Start Moveing
 * 
 *  3-check if failure happen in Delivery Cargos Journey
 *	4-Check if there's failure happen
 * 
 *	5-deliver Cargo
 *	6-check if Truck finished Delivery
 *  7-End Journey OR return Home
 * 
 *  8-See if need CheckUP and get it if needed
 *	9-end checkup
*/

bool Truck::AssignCargo(Cargo* c, const Time& currentTime, bool isNightAlready)
{
	// Handel 1 : Night Shift AND loading Time
	if ((isNightAlready && !isNightShift) || currentTime < FinishingLoadingTime) return false;

	// set Cargo's LoadedTruck to this Truck
	c->setLoadingTruck(this);
	//add cargo according to First to arrive

	/// change later in Move to CargoDeliveryTime 
	/// For Better Handeling Unstable sort
	loadedCargo->enqueue(c, (c->GetDist()));

	//Handel 2 : set New Finish Loading Time
	FinishingLoadingTime = currentTime + c->GetLt();
	
	MaxCargoDist = MaxCargoDist > c->GetDist() ? MaxCargoDist : c->GetDist();//get Max Distance will Truck Cut till Now
	return true;
}
bool Truck::move(const Time* t)
{
	/*
	* @Summary Function
	*	First : check if Truck Can Move now By Maxwait or by truck Capacity
	*	Second : if True set MovingTime by currentTime
	*			 By change all cargos delivery Time and waiting Time
	*			 increase total avtive time of truck
	*		     calculate and set Delivery interval of truck
	*/


	//Not Moving When
		//1-if not forced to move (MaxWait) [AND] Capacity Rule Not Applicable
		//2-[OR] not finished loading
	if (!NowMoving && Capcity > loadedCargo->getSize() || *t < FinishingLoadingTime) return false;
	
	//set moving time with current Time
	MT = *t;

	int prevLoadingTime = 0;
	PriorityQueue<Cargo*>* aux = new PriorityQueue<Cargo*>(Capcity); //cargos that assigned on truck
	while (!loadedCargo->isEmpty()) {

		//1-get pointer to smallest cargo distance [first to deliver]
		Cargo* c = loadedCargo->peekFront();

		//2-set waitingTime and CargoDeliveryTime of cargo
		// 
		// 
		//accumlate loading Time of previous cargo
		//for handeling loading||unloading Cargos one by one
		prevLoadingTime += c->GetLt();
		c->setCDT(MT + ceil(c->GetDist() / Speed) + prevLoadingTime);//calculate cargo Delivery Time 
																		//using all [previous Cargos Loading Time] + current Time + Travel Time
		c->SetWt( MT -  c->GetPt() );//calculate WaitingTime of Cargo
		



		//3-deleted it from [loadedCargo] and sotre it in [aux]  for loop
		aux->enqueue(c, c->getCDT().ConvertToInt());//set CDT a priority Key
														   //so First Cargos To Deliver are put first in Queue
		loadedCargo->dequeue();
		
	}

	//increase total active time by [Loading + unloading + Interval that truck travel]
	tAT += 2 * prevLoadingTime + ceil(MaxCargoDist / Speed);
	//calculate deliver interval by [unloading Time + Time to go of travel & return back]
	DI.setHour(prevLoadingTime + 2 * ceil(MaxCargoDist / Speed));
	
	//FOR: memory managment
	delete loadedCargo;
	loadedCargo = aux;

	return true;		
}

bool Truck::getIsFailed() const{return isFailed;}
void Truck::Failuer(const Time* t, UI * uiPtr)
{

	/*
	* @Summary Function
	*	First : generate a random and check Probability
	*	Second : if True set Truck to return home
	*			 By change all cargos delivery Time
	*			 set bool isFaild[means that ruck failed to deliver Cargos and return back to home]
	*		     change MovingTime of truck by now && change DI by interval to come back to home
	*/

	//for not repeating rand function
	srand(time(0));

	//if Propapility is False || is failed already Once
	if (rand() % 100 >= 5 || isFailed) return;

	//print msg of failure and play music && set that the truck already failed
	uiPtr->Output("Failure Happen : " + to_string(ID) + " is Failed and need maintaince.\n");
	PlaySound(TEXT("WHY1.wav"), NULL, SND_FILENAME);
	isFailed = true;
	//print msg of failure and play music && set that the truck already failed


	int prev = 0;//store all prev (unloading||loading) Time of previous Cargos
				//Handel That Cargo (Load||unload) one by one

	//Create auxilary space to store cargos dequeued from LoadedCargo Of Truck
	//when loop in CargosLoaded in Truck 
	PriorityQueue<Cargo*>* aux = new PriorityQueue<Cargo*>(Capcity);
	
	//loop till loadedCargo is Empty (through all cargos)
	while (!loadedCargo->isEmpty())
	{
		//1-get First Cargo in loadedCargo
		Cargo* c = loadedCargo->peekFront();

		//2 - increase total [loadingTime || unloadingTime] of all previous cargos in truck
		prev += c->GetLt();

		//4 - calculate cargo Delivery Time 
			//using all [previous Cargos Loading Time] + current Time + Travel Time
		c->setCDT(*t + (*t - MT) + prev);

		
		//5-deleted it from [loadedCargo] and sotre it in [aux]  for loop
		aux->enqueue(c,c->getCDT().ConvertToInt());//set CDT a priority Key
														   //so First Cargos To Deliver are put first in Queue
		loadedCargo->dequeue();

	}
	//For memory management
	delete loadedCargo;
	loadedCargo = aux;

	//set Moving Time of Truck with current Time
	MT = *t;
	//calculate Delivery Interval
	DI  = (*t - MT) + prev;
}

Cargo* Truck::DeliverCargos(const Time& currentTime)
{
	//Check 1: if there's Cargo in loaded Cargos in Truck
	if (loadedCargo->isEmpty()) return NULL;
	//Check 2: if Cargo with nearest CargoDeliveryTime passed or happen Now
	if (loadedCargo->peekFront()->getCDT() <= currentTime) {
		//store it and return it after remove it from loaded Cargos of truck
		Cargo* c = loadedCargo->peekFront();
		loadedCargo->dequeue();
		tDC++; // increase total Delivered Cargos
		return c;
	}
	return NULL;
}
bool Truck::isFinishedDelivery(const Time& currentTime ) const
{
	return DI + MT <= currentTime;
}
void Truck::EndJourney() {
	//increase number of journeys
	numberOfJourney++;
	totalJouneys++;

	//reset all journey properties to zero and false again
	MaxCargoDist = 0;
	NowMoving = false;
	MT.setDay(0);
	MT.setHour(0);
	DI.setDay(0);
	DI.setHour(0);
	FinishingLoadingTime.setDay(0);
	FinishingLoadingTime.setHour(0);
}

bool Truck::CheckUP(const Time & currentTime, int J , UI*uiptr) {
	//BONUS : For Random CheckUP
	srand(time(0));
	bool maintainP;
	maintainP = rand() % 100 < 5;
	//check maintain propalitiy || if the truck failed || end number of journey
	if (maintainP || isFailed || numberOfJourney >= J) {
		//set finish checkup time of truck
		FinishingCheckUPTime = currentTime + GetCheckUPTime();

		//print Message to check if Bonus Work
		if (maintainP)
			uiptr->Output("Maintiance apart happened to truck Number:"+to_string(ID) + "\n");
		return true;
	}
	return false;
}
bool Truck::isFinishedCheckUp(const Time& currentTime) const { return ( FinishingCheckUPTime <=currentTime ); }
void Truck::endCheckUp()
{
	//reset checkup properties
	numberOfJourney = 0; // to start count again number of journeys Before check up
	FinishingCheckUPTime.setDay(0);
	FinishingCheckUPTime.setHour(0);
	isFailed = false;
}

Truck::~Truck() {
	delete loadedCargo;
}
 