#include "Company.h"
#include "PreparationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include"UI.h"
#include<fstream>
#include<string>
using namespace std;

Company::Company() {

	//initalize IO & UI
	 IN_PATH = "Input_File.txt";
	 OUT_PATH="Output_File.txt";
	 uiPtr = new UI;
	 load();
	 Out_Start();
	//initalize IO & UI


	 //inialize Trucks
	 loadingTrucks.insert(Normal, NULL);
	 loadingTrucks.insert(Special, NULL);
	 loadingTrucks.insert(VIP, NULL);
	 for (int i = 0; i < NormalTruckCount; i++) {
		 emptyTrucks[Normal].enqueue(new NormalTruck);
	 }
	 for (int i = 0; i < SpecialTruckCount; i++) {
		 emptyTrucks[Special].enqueue(new SpecialTruck);
	 }
	 for (int i = 0; i < VIPTruckCount; i++) {
		 emptyTrucks[VIP].enqueue(new VIPTruck);

	 }
	 movingTrucks = new PriorityQueue<Truck *>(getEmptyTrucksCount());
	 //inialize Trucks
	 
	 
	 //inialize Counters
	 NormalCargoCount = SpecialCargoCount = VIPCargoCount = 0;
	 TotalTruckActiveTime = TotalTruckUtilization = PromotedCargoCount = 0;


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
	EndSimulation();
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


///////////////////////////////////////////////////Change states of Trucks
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
			maintainingTrucks[trucktype].peekFront()->endCheckUp();
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
inline bool Company::AutoPCheck(Cargo* c)
{
	return (currentTime.getDay() - c->GetPt().getDay() >= AutoP && currentTime.getHour() == c->GetPt().getHour());
}
void Company::Promote(Cargo* c)
{
	c->setTypes('V');
	waitingVIPCargo.enqueue(c, c->getPriority());
	PromotedCargoCount++;
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
		TotalCargoWait = TotalCargoWait + temp->GetWt();
		file << '\t' << temp->getID() << '\t' << temp->GetPt().TimePrint() << '\t' << temp->GetWt().TimePrint() << '\t' << temp->getLoadingTruck()->getID() << '\n';
	}
	file.close();
}

void Company::EndSimulation(){
	for(int i = 0;i < 3;i++){
		while (!emptyTrucks[i].isEmpty()) {
			Truck* t = emptyTrucks[i].peekFront();
			//cout << t->getTotalActiveTime() << ' ';
			TotalTruckActiveTime += t->getTotalActiveTime();
			TotalTruckUtilization += t->getTruckUtilization(currentTime);
			emptyTrucks[i].dequeue();
		}
	}
	Out_End();
	
}

void Company::Out_End() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	int TotalTrucksCount = NormalTruckCount + SpecialTruckCount + VIPTruckCount;
	file << ".........................................\n";
	file << ".........................................\n";
	file << "Cargos: " << getDeliveredCargosCount() << "[N: " << DeliveredCargos[0].getSize() << ", S: " << DeliveredCargos[1].getSize() << ", V: " << DeliveredCargos[2].getSize() << "]";
	file << "\nCargo Avg Wait = " << Time(0,TotalCargoWait.ConvertToInt() / getDeliveredCargosCount()).TimePrint();
	file << "\nAuto-Promoted Cargos : " << PromotedCargoCount/ getDeliveredCargosCount()*100 << "%\n";
	file << "Trucks: " << TotalTrucksCount << "[N: " << NormalTruckCount << ", S: " << SpecialTruckCount << ", V: " << VIPTruckCount << "]";
	file << "\nAvg Active Time = " << TotalTruckActiveTime  / ((double)currentTime.ConvertToInt() * TotalTrucksCount) * 100 << '%';
	file << "\nAvg utilization = " << TotalTruckUtilization / TotalTrucksCount * 100 << "%\n";
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

inline bool Company::isSimulationEnd() {
	return  (
		EventList.isEmpty() &&
		waitingNormalCargo.isEmpty() &&
		waitingSpecialCargo.isEmpty() &&
		waitingVIPCargo.isEmpty() &&
		!getLoadingTrucksCount() &&
		movingTrucks->isEmpty() &&
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



bool Company::CheckFailure(Truck* t)
{
	if (t->getFailure())
	{
		while (!(t->getCargoList()->isEmpty()))
		{
			Cargo* temp = t->getCargoList()->peekFront();
			t->getCargoList()->dequeue();
			if (temp->getType() == VIP)
			{
				waitingVIPCargo.enqueue(temp, temp->getPriority() );
			}
			if (temp->getType() == Normal)
			{
				waitingNormalCargo.addBack(temp);
			}
			if (temp->getType() == Special)
			{
				waitingSpecialCargo.enqueue(temp);
			}
		}
		Types x = t->getTruckType();
		// t->EndJourney(); check 
		maintainingTrucks[x].enqueue(t);
		uiPtr->Print(191);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////MaxW
inline bool Company::MaxWCheck(Cargo* c) {return (currentTime - c->GetPt() >= MaxW && !c->getLoadingTruck());}

///////////////////////////////////////////////////MaxW
void Company::checkLoadingTrucks()
{

	// vip cargo assignment 
	// 1st assign in vip trucks 
	if (!loadingTrucks.getEntry(VIP) && !waitingVIPCargo.isEmpty())
	{
		////1st case assign in VIP Trucks
		//if (!emptyTrucks[VIP].isEmpty())
		//	truck_temp = emptyTrucks[VIP].peekFront();
		//
		//// 2nd case assign in normal trucks if there is no available vip trucks 
		//else if (emptyTrucks[VIP].isEmpty() && !emptyTrucks[Normal].isEmpty())
		//	truck_temp = emptyTrucks[Normal].peekFront();
		//
		////3rd case assign in special trucks
		//else if (emptyTrucks[VIP].isEmpty() && emptyTrucks[Normal].isEmpty() && !emptyTrucks[Special].isEmpty())
		//	truck_temp = emptyTrucks[Special].peekFront();
		//
		//addLoadingTruck(truck_temp, VIP, waitingVIPCargo.getSize());
		int c = waitingVIPCargo.getSize();
		if (!emptyTrucks[VIP].isEmpty() && !addLoadingTruck(emptyTrucks[VIP].peekFront(), VIP, c));
		else if(!emptyTrucks[Normal].isEmpty() && !addLoadingTruck(emptyTrucks[Normal].peekFront(), VIP, c));
		else if(!emptyTrucks[Special].isEmpty())
			addLoadingTruck(emptyTrucks[Special].peekFront(), VIP, c);
	}


	//! Asignment of special cargos
	if (!loadingTrucks.getEntry(Special) && !emptyTrucks[Special].isEmpty() && !waitingSpecialCargo.isEmpty()){
		addLoadingTruck(emptyTrucks[Special].peekFront(), Special, waitingSpecialCargo.getSize(), MaxWCheck(waitingSpecialCargo.peekFront()));
	}


	if(!loadingTrucks.getEntry(Normal) && !waitingNormalCargo.isEmpty()){
		//if (MaxWCheck(waitingNormalCargo.getFront()) && !(emptyTrucks[Normal].isEmpty() && emptyTrucks[VIP].isEmpty())) {

		//	Types t = Normal;
		//	if (emptyTrucks[Normal].isEmpty())
		//		t = VIP;
		//	
		//	emptyTrucks[t].peekFront()->setNowMoving(true);
		//	truck_temp = emptyTrucks[t].peekFront();
		//}
		//else {
		//	if (!emptyTrucks[Normal].isEmpty() && emptyTrucks[Normal].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
		//		truck_temp = emptyTrucks[Normal].peekFront();

		//	else if (emptyTrucks[Normal].isEmpty() && !emptyTrucks[VIP].isEmpty() && emptyTrucks[VIP].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
		//		truck_temp = emptyTrucks[VIP].peekFront();
		//}
		//addLoadingTruck(truck_temp, Normal);
		bool Now = MaxWCheck(waitingNormalCargo.getFront());
		int c = waitingNormalCargo.getSize();
		if (!emptyTrucks[Normal].isEmpty() && !addLoadingTruck(emptyTrucks[Normal].peekFront(), Normal , c, Now));
		else if (!emptyTrucks[VIP].isEmpty() && !addLoadingTruck(emptyTrucks[VIP].peekFront(), Normal, c, Now));
	}

}
bool Company::addLoadingTruck(Truck * t, Types CargoType, int MinCapacity, bool Now)
{
	if (!t) return false;
	if (Now || t->GetCapcity() <= MinCapacity) {
		emptyTrucks[t->getTruckType()].dequeue();
		loadingTrucks.setEntry(CargoType, t);
		t->setNowMoving(Now);
		return true;
	}
	return false;
}



void Company::moveTrucks()
{
	for (int i = 0; i < loadingTrucks.getSize(); i++) {
		Truck* t = loadingTrucks.getEntry(i);
		if ( t && t->move(&currentTime)) {
			loadingTrucks.setEntry(i, NULL);

			movingTrucks->enqueue(t, (t->GetDi() + t->GetMt()).ConvertToInt());
			MovingCargoCount += t->getCargoList()->getSize();
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
		//if (CheckFailure(t))
		//{
		//	return;
		//}
		aux->enqueue(t, (t->GetDi() + t->GetMt()).ConvertToInt());

		///Handeling DeliverCargo One By One
		Cargo* c = t->DeliverCargos(currentTime);
		while (c) {
			DeliveredCargos_temp.enqueue(c);
			MovingCargoCount--;
			c = t->DeliverCargos(currentTime);
		}

	}
	//t->EndJourney();
	delete movingTrucks;
	movingTrucks = aux;
}



///////////////////////////////////////GETTERS

////////////////////////Counters
int Company::getWaitingCargosCount() const {

	return waitingNormalCargo.getSize() + waitingSpecialCargo.getSize() + waitingVIPCargo.getSize();
}
int Company::getEmptyTrucksCount() const {
	return NormalTruckCount + SpecialTruckCount + VIPTruckCount;
}
int Company::getMovingCargosCount() const { return MovingCargoCount;}
int Company::getLoadingTrucksCount() const { 
	int count = 0;
	for (int i = 0; i <= VIP; i++)
		count+= bool(loadingTrucks.getEntry(i));
	return count;
}
int Company::getMaintainingTrucksCount() const {
	return maintainingTrucks[Normal].getSize() + maintainingTrucks[Special].getSize() + maintainingTrucks[VIP].getSize();
}
int Company::getDeliveredCargosCount() const { return DeliveredCargos[0].getSize() + DeliveredCargos[1].getSize() + DeliveredCargos[2].getSize(); }
////////////////////////Counters

const Time & Company::getCurrentTime() const {
	return currentTime;
}

////////////////////////Cargos
 LinkedList<Cargo*>& Company::getWaitingNormalCargo() {return waitingNormalCargo;}
 Queue<Cargo*>& Company::getWaitingSpecialCargo() {return waitingSpecialCargo;}
 PriorityQueue<Cargo*>& Company::getWaitingVIPCargo()
 {return waitingVIPCargo;}
const Queue<int>* Company::getDeliveredCargo()const { return DeliveredCargos; }
////////////////////////Cargos


////////////////////////Trucks
const Queue<Truck*>* Company::getEmptyTrucks() const { return emptyTrucks; }
const List<Truck*>& Company::getLoadingTrucks() const { return loadingTrucks; }
const PriorityQueue< Truck*>* Company::getMovingTrucks() const { return movingTrucks; }
const Queue< Truck*>* Company::getMaintainingTrucks() const { return maintainingTrucks; }
////////////////////////Trucks


Company::~Company() {
	delete movingTrucks;
	delete uiPtr;
}