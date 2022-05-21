#include "Company.h"
#include "PreparationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include"UI.h"
#include<fstream>
#include<string>
using namespace std;

Company::Company() {
	 IN_PATH = "Input_File.txt";
	 OUT_PATH="Output_File.txt";
	 loadingTrucks.insert(Normal, NULL);
	 loadingTrucks.insert(Special, NULL);
	 loadingTrucks.insert(VIP, NULL);
	 uiPtr = new UI;
	 uiPtr->ReadMode();
	 load();
	 Out_Start();
	 movingTrucks = new PriorityQueue<Truck *>(getEmptyTrucksCount());
	 for (int i = 0; i < NormalTruckCount; i++) {
		 emptyTrucks[Normal].enqueue(new NormalTruck);
	 }
	 for (int i = 0; i < SpecialTruckCount; i++) {
		 emptyTrucks[Special].enqueue(new SpecialTruck);
	 }
	 for (int i = 0; i < VIPTruckCount; i++) {
		 emptyTrucks[VIP].enqueue(new VIPTruck);

	 }
}

void Company::Simulate() {


	while (!isSimulationEnd())
	{
			ExecuteEvent();

			AutoPromotion();

			moveTrucks();

			DeliverCargos();
			Movingcheck();
			EndCheckUP();


			Out_Mid();
		if(currentTime.getHour() >= 5 && currentTime.getHour() <=23){
			checkLoadingTrucks();
			assign();
		}
			uiPtr->Print(this);
			

		currentTime.Update();
	}
	Out_End();
		//TODO: [statics]
}

///////////////////////////////////////////////////Change states of Trucks
//////////////booleans for states
bool Company::isFinishedCheckUP(Truck* t)
{
	//True = Finish isFinishedCheckUP
	//false = otherwise
	//t->GetMt() + t->GetDi() = time truck return to company
	return (currentTime - (t->GetMt() + t->GetDi()) >=  t->GetCheckUPTime());
}
inline bool Company::isFinishedDelivery(Truck* t) {
	return (movingTrucks->peekFront()->GetDi() + movingTrucks->peekFront()->GetMt() <= currentTime);
}
inline bool Company::NeedCheck(Truck* t)
{
	//True : 
	return(J >= t->getNumberOfJourney());
}
//////////////booleans for states

void Company::Movingcheck()
{
	//if Finished Move 
		//
	while (!movingTrucks->isEmpty()&& isFinishedDelivery(movingTrucks->peekFront()))
	{
		Truck* temp = movingTrucks->peekFront();
		temp->EndJourney();
		movingTrucks->dequeue();
		//DeliverCargos(temp);
		Queue<Truck *>* listAddedTo = NULL;

		Types t= Normal;
		if (dynamic_cast<VIPTruck*>(temp))
			t= VIP;
		else if (dynamic_cast<SpecialTruck*>(temp))
			t = Special;


		if (NeedCheck(temp))
			temp->SetNumberOfJourney(0),
			listAddedTo = &maintainingTrucks[t];
		else
			listAddedTo = &emptyTrucks[t];
		
		listAddedTo->enqueue(temp);
	}
	/// 
}
void Company::EndCheckUP() {
	for (int trucktype = 0; trucktype <= VIP; trucktype++) {

		while (!maintainingTrucks[trucktype].isEmpty() && isFinishedCheckUP(maintainingTrucks[trucktype].peekFront()))
		{
			emptyTrucks[trucktype].enqueue(maintainingTrucks[trucktype].peekFront());
			maintainingTrucks[trucktype].peekFront()->resetFinishingCheckUPTime();
			maintainingTrucks[trucktype].dequeue();
		}
	}
}
///////////////////////////////////////////////////Change states of Trucks



///////////////////////////////////////////////////AutoP
void Company::AutoPromotion() {
	while (!waitingNormalCargo.isEmpty() && AutoPCheck(waitingNormalCargo.getFront()))
	{
		Cargo* temp = waitingNormalCargo.getFront();
		waitingNormalCargo.removeFront();
		Promote(temp);
	}
	while (!waitingSpecialCargo.isEmpty() && AutoPCheck(waitingSpecialCargo.peekFront()))
	{
		Cargo* temp = waitingSpecialCargo.peekFront();
		waitingSpecialCargo.dequeue();
		Promote(temp);
	}
}
bool Company::AutoPCheck(Cargo* c)
{
	return (currentTime.getDay() - c->GetPt().getDay() >= AutoP && currentTime.getHour() == c->GetPt().getHour());

}
void Company::Promote(Cargo* c)
{
	c->setTypes('V');
	getWaitingVIPCargo().enqueue(c, c->getPriority());
}
///////////////////////////////////////////////////AutoP


///////////////////////////////////////////////////I/O
void Company::Out_Start() {
	ofstream file;
	file.open(OUT_PATH);
	file << "CDT\tID\tPT\tWT\tTID\n";
	file.close();
}
void Company::Out_Mid() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	while (!DeliveredCargos_temp.isEmpty()) {
		Cargo* temp = DeliveredCargos_temp.peekFront();
		DeliveredCargos[temp->getType()].enqueue(temp->getID());
		DeliveredCargos_temp.dequeue();
		file << temp->getCDT().TimePrint();
		file << '\t' << temp->getID() << '\t' << temp->GetPt().TimePrint() << '\t' << temp->GetWt().TimePrint() << '\t' << temp->getLoadingTruck()->getID() << '\n';
	}
	file.close();
}
void Company::Out_End() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	int TotalTrucksCount = NormalTruckCount + SpecialTruckCount + VIPTruckCount;
	file << ".........................................\n";
	file << ".........................................\n";
	file << "Cargos: " << getDeliveredCargosCount() << "[N: " << NormalCargoCount << ", S: " << SpecialCargoCount << ", V: " << VIPCargoCount << "]";
	file << "\nCargo Avg Wait = " << CargoAvgWait.TimePrint(); 
	file << "\nAuto-Promoted Cargos : " << PromotedCargoCount << "%\n";
	file << "Trucks: " << TotalTrucksCount << "[N: " << NormalTruckCount << ", S: " << SpecialTruckCount << ", V: " << VIPTruckCount << "]";
	file << "\nAvg Active Time = " << TotalTruckActiveTime / TotalTrucksCount * 100 << '%';
	file << "\nAvg utilization = " << TotalTruckUtilization / TotalTrucksCount * 100 << '\n';
	file.close();
}
void Company::load()
{
	ifstream file;

	file.open(IN_PATH);

	file >> NormalTruckCount; 
	file >> SpecialTruckCount;
	file >> VIPTruckCount;

	float speed;
	file>> speed;
	NormalTruck::SetSpeed(speed);

	file>> speed;
	SpecialTruck::SetSpeed(speed);

	file>> speed;
	VIPTruck::SetSpeed(speed);

	int capacity;
	file >> capacity;
	NormalTruck::SetCapcity(capacity);

	file >> capacity;
	SpecialTruck::SetCapcity(capacity);

	file >> capacity;
	VIPTruck::SetCapcity(capacity);

	int CheckUPTime;
	file >> CheckUPTime;
	NormalTruck::setCheckUPTime(CheckUPTime);

	file >> CheckUPTime;
	SpecialTruck::setCheckUPTime(CheckUPTime);

	file >> CheckUPTime;
	VIPTruck::setCheckUPTime(CheckUPTime);

	file >> J;

	file >> AutoP;
	file >> MaxW;

	int EventNumber;
	file >> EventNumber;
	Event* newEvent = nullptr;
	for (int i = 0; i < EventNumber; i++)
	{
		char eventType;
		file >> eventType;
		switch (eventType)
		{
		case 'R':
			newEvent = new PreparationEvent;
			break;
		case 'X':
			newEvent = new CancellationEvent;
			break;
		case 'P':
			newEvent = new PromotionEvent;
			break;
		default:
			break;
		}
		newEvent->Read(file);
		EventList.enqueue(newEvent);
	}
	file.close();
}
///////////////////////////////////////////////////I/O

bool Company::isSimulationEnd() {
	return  (
		EventList.isEmpty() &&
		waitingNormalCargo.isEmpty() &&
		waitingSpecialCargo.isEmpty() &&
		waitingVIPCargo.isEmpty() &&
		loadingTrucks.isEmpty() &&
		maintainingTrucks[0].isEmpty() &&
		maintainingTrucks[1].isEmpty() &&
		maintainingTrucks[2].isEmpty()
		);
}

void Company::ExecuteEvent() {
	while (!EventList.isEmpty() && currentTime == EventList.peekFront()->getEventTime())
	{
		EventList.peekFront()->Execute(this);
		delete EventList.peekFront();
		EventList.dequeue();
	}

}

void Company::assign() {
	if (loadingTrucks.getEntry(Normal) && !waitingNormalCargo.isEmpty())
		if (loadingTrucks.getEntry(Normal)->AssignCargo(waitingNormalCargo.getFront(), currentTime))
		{   // changes to calculate the DI distance
			waitingNormalCargo.removeFront();
		}
	if (loadingTrucks.getEntry(Special) && !waitingSpecialCargo.isEmpty())
		if (loadingTrucks.getEntry(Special)->AssignCargo(waitingSpecialCargo.peekFront(), currentTime))
		{
			waitingSpecialCargo.dequeue();
		}

	if (loadingTrucks.getEntry(VIP) && !waitingVIPCargo.isEmpty())
		if (loadingTrucks.getEntry(VIP)->AssignCargo(waitingVIPCargo.peekFront(), currentTime))
		{
			waitingVIPCargo.dequeue();
		}
}

///////////////////////////////////////////////////MaxW
bool Company::MaxWCheck(Cargo* c) {return (currentTime - c->GetPt() >= MaxW && !c->getLoadingTruck());}

///////////////////////////////////////////////////MaxW
void Company::checkLoadingTrucks()
{
	// vip cargo assignment 
	// 1st case assign in vip trucks 
	if (!loadingTrucks.getEntry(VIP) && !waitingVIPCargo.isEmpty())
	{
		if (!emptyTrucks[VIP].isEmpty() && emptyTrucks[VIP].peekFront()->GetCapcity() <= waitingVIPCargo.getSize())
			addLoadingTruck(VIP, VIP);
		// 2nd case assign in normal trucks if there is no available vip trucks 
		else if (emptyTrucks[VIP].isEmpty() && !emptyTrucks[Normal].isEmpty() && emptyTrucks[Normal].peekFront()->GetCapcity() <= waitingVIPCargo.getSize())
			addLoadingTruck(Normal, VIP);
		//3rd case assign in special trucks
		else if (emptyTrucks[VIP].isEmpty() && emptyTrucks[Normal].isEmpty() && !emptyTrucks[Special].isEmpty() && emptyTrucks[Special].peekFront()->GetCapcity() <= waitingVIPCargo.getSize())
			addLoadingTruck(Special, VIP);
			//waitingVIPCargo.dequeue();
			//t->AssignCargo(v);
	}

	//! Asignment of special cargos
	if (!loadingTrucks.getEntry(Special) && !emptyTrucks[Special].isEmpty() && !waitingSpecialCargo.isEmpty()){
		if (MaxWCheck(waitingSpecialCargo.peekFront())) {
			emptyTrucks[Special].peekFront()->setNowMoving(true);
			addLoadingTruck(Special, Special);
/*			

			emptyTrucks[Special].peekFront()->AssignCargo(waitingSpecialCargo.peekFront(), currentTime);

			loadingTrucks.insert(loadingTrucks.getSize(), emptyTrucks[Special].peekFront());

			waitingSpecialCargo.dequeue();
			emptyTrucks[Special].dequeue()*/;
		}

		// 
		else if(emptyTrucks[Special].peekFront()->GetCapcity() <= waitingSpecialCargo.getSize())
			addLoadingTruck(Special, Special);
	}


	if(!loadingTrucks.getEntry(Normal) && !waitingNormalCargo.isEmpty()){
		if (MaxWCheck(waitingNormalCargo.getFront()) && !(emptyTrucks[Normal].isEmpty() && emptyTrucks[VIP].isEmpty())) {

			Types t = Normal;
			if (emptyTrucks[Normal].isEmpty())
				t = VIP;
			
			emptyTrucks[t].peekFront()->setNowMoving(true);
			addLoadingTruck(t, Normal);
			/*emptyTrucks[t].peekFront()->move(&currentTime);
			emptyTrucks[t].peekFront()->setNowMoving(true);

			emptyTrucks[t].peekFront()->AssignCargo(waitingNormalCargo.getFront(), currentTime);

			loadingTrucks.insert(loadingTrucks.getSize(), emptyTrucks[t].peekFront());

			waitingNormalCargo.removeFront();
			emptyTrucks[t].dequeue();*/
		}
		else {
			if (!emptyTrucks[Normal].isEmpty() && emptyTrucks[Normal].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
				addLoadingTruck(Normal, Normal);

			else if (emptyTrucks[Normal].isEmpty() && !emptyTrucks[VIP].isEmpty() && emptyTrucks[VIP].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
				addLoadingTruck(VIP, Normal);
		}
	}

}
void Company::addLoadingTruck(Types truckType, Types CargoType)
{
	Truck *t = emptyTrucks[truckType].peekFront();
	emptyTrucks[truckType].dequeue();
	loadingTrucks.setEntry(CargoType, t);
}

void Company::moveTrucks()
{
	for (int i = 0; i < loadingTrucks.getSize(); i++) {
		Truck* t = loadingTrucks.getEntry(i);
		if ( t && t->move(&currentTime)) {
			if (i < 3)
				loadingTrucks.setEntry(i, NULL);
			else
				loadingTrucks.remove(i);

			movingTrucks->enqueue(t, (t->GetDi() + t->GetMt()).ConvertToInt());
			MovingCargoCount += t->getNowMoving() ? 1 : t->GetCapcity();
		}
	}
}
// calculate the finish time of delivery

void Company::DeliverCargos()
{
	PriorityQueue<Truck*>* aux = new PriorityQueue<Truck*>(getEmptyTrucksCount());
	while (!movingTrucks->isEmpty()) {
		//Handeling Loop
		Truck* t = movingTrucks->peekFront();
		movingTrucks->dequeue();
		aux->enqueue(t, (t->GetDi() + t->GetMt()).ConvertToInt());

		///Handeling DeliverCargo One By One
		Cargo* c = t->DeliverCargos(currentTime);
		while (c) {
			DeliveredCargos_temp.enqueue(c);
			c = t->DeliverCargos(currentTime);
		}

	}
	//t->EndJourney();
	delete movingTrucks;
	movingTrucks = aux;
}
//void Company::UpdateStatics(){}






///////////////////////////////////////GETTERS

int Company::getWaitingCargosCount() const {

	return waitingNormalCargo.getSize() + waitingSpecialCargo.getSize() + waitingVIPCargo.getSize();
}
int Company::getEmptyTrucksCount() const {
	return emptyTrucks[Normal].getSize() + emptyTrucks[Special].getSize() + emptyTrucks[VIP].getSize();
}
int Company::getMovingCargosCount() const { return MovingCargoCount; }
int Company::getMaintainingTrucksCount() const {
	return maintainingTrucks[Normal].getSize() + maintainingTrucks[Special].getSize() + maintainingTrucks[VIP].getSize();
}
int Company::getDeliveredCargosCount() const { return DeliveredCargos[0].getSize() + DeliveredCargos[1].getSize() + DeliveredCargos[2].getSize(); }

const Time & Company::getCurrentTime() const {
	return currentTime;
}

LinkedList<Cargo*>& Company::getWaitingNormalCargo() {return waitingNormalCargo;}
Queue<Cargo*>& Company::getWaitingSpecialCargo() {return waitingSpecialCargo;}
PriorityQueue<Cargo*>& Company::getWaitingVIPCargo(){return waitingVIPCargo;}
const Queue<int>* Company::getDeliveredCargo()const { return DeliveredCargos; }


const Queue<Truck*>* Company::getEmptyTrucks() const { return emptyTrucks; }
const List<Truck*>& Company::getLoadingTrucks() const { return loadingTrucks; }
const PriorityQueue< Truck*>* Company::getMovingTrucks() const { return movingTrucks; }
const Queue< Truck*>* Company::getMaintainingTrucks() const { return maintainingTrucks; }


Company::~Company() {
	for(int i = 0;i < 3;i++)
		while (!emptyTrucks[i].isEmpty()) emptyTrucks[i].dequeue();
	delete movingTrucks;
	delete uiPtr;
}