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
	
	 movingTrucks = new PriorityQueue<Truck*>(getTotalTruckCount());
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
			TrucksReturnBack();
			EndCheckUP();
			Out_Mid();
			checkLoadingTrucks();
			assign(NightMode());
			uiPtr->Print(this);
			

		currentTime.Update();
	}
	EndSimulation();
		//TODO: [statics]
}


///////////////////////////////////////////////////Change states of Trucks
//////////////booleans for states

//////////////booleans for states


///////////////////////////////////////////////////Change states of Trucks
void Company::TrucksReturnBack()
{
	//if Finished Move 
	while (!movingTrucks->isEmpty()&& movingTrucks->peekFront()->isFinishedDelivery(currentTime))
	{
		Truck* temp = movingTrucks->peekFront();
		temp->EndJourney();
		movingTrucks->dequeue();
		//DeliverCargos(temp);
		Queue<Truck *>* listAddedTo = NULL;

		Types t= temp->getTruckType();

		if (temp->CheckUP(currentTime, J,uiPtr))
			maintainingTrucks[t].enqueue(temp);
		else if(temp->getIsNightShift())
			NightTrucks[t].enqueue(temp, temp->getPriority());
		else
			emptyTrucks[t].enqueue(temp, temp->getPriority());
	}
	/// 
}

void Company::EndCheckUP() {
	for (int trucktype = 0; trucktype <= VIP; trucktype++) {

		while (!maintainingTrucks[trucktype].isEmpty() && maintainingTrucks[trucktype].peekFront()->isFinishedCheckUp(currentTime))
		{
			Truck* t = maintainingTrucks[trucktype].peekFront();
			if(t->getIsNightShift())
				NightTrucks[trucktype].enqueue(t, t->getPriority());
			else
				emptyTrucks[trucktype].enqueue(t, t->getPriority());
			t->endCheckUp();
			maintainingTrucks[trucktype].dequeue();
		}
	}
}
///////////////////////////////////////////////////Change states of Trucks



///////////////////////////////////////////////////AutoP
void Company::AutoPromotion() {
	while (!waitingNormalCargo.isEmpty() && waitingNormalCargo.getFront()->AutoPCheck(currentTime, AutoP))
	{
		Cargo* temp = waitingNormalCargo.getFront();
		waitingNormalCargo.removeFront();
		Promote(temp);
	}
	while (!waitingSpecialCargo.isEmpty() && waitingSpecialCargo.peekFront()->AutoPCheck(currentTime, AutoP))
	{
		Cargo* temp = waitingSpecialCargo.peekFront();
		waitingSpecialCargo.dequeue();
		Promote(temp);
	}
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
			TotalTruckActiveTime += t->getTotalActiveTime();
			TotalTruckUtilization += t->getTruckUtilization(currentTime);
			emptyTrucks[i].dequeue();
		}
	}

	for (int i = 0; i < 3; i++) {
		while (!NightTrucks[i].isEmpty()) {
			Truck* t = NightTrucks[i].peekFront();
			TotalTruckActiveTime += t->getTotalActiveTime();
			TotalTruckUtilization += t->getTruckUtilization(currentTime);
			NightTrucks[i].dequeue();
		}
	}

	Out_End();
	
}

void Company::Out_End() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	file << ".........................................\n";
	file << ".........................................\n";
	file << "Cargos: " << getDeliveredCargosCount() << "[N: " << DeliveredCargos[0].getSize() << ", S: " << DeliveredCargos[1].getSize() << ", V: " << DeliveredCargos[2].getSize() << "]";
	file << "\nCargo Avg Wait = " << Time(0,TotalCargoWait.ConvertToInt() / getDeliveredCargosCount()).TimePrint();
	file << "\nAuto-Promoted Cargos : " << PromotedCargoCount/ getDeliveredCargosCount()*100 << "%\n";
	file << "Trucks: " << getTotalTruckCount() << "[N: " << NormalTruckCount << ", S: " << SpecialTruckCount << ", V: " << VIPTruckCount << "]";
	file << "\nAvg Active Time = " << TotalTruckActiveTime  / ((double)currentTime.ConvertToInt() * getTotalTruckCount()) * 100 << '%';
	file << "\nAvg utilization = " << TotalTruckUtilization / getTotalTruckCount() * 100 << "%\n";
	file.close();
}
void Company::load()
{
	ifstream file;

	file.open(IN_PATH);

	file >> NormalTruckCount; 
	for (int i = 0; i < NormalTruckCount; i++) {
		Truck* t = new NormalTruck(file);
		if (t->getIsNightShift())
			NightTrucks[Normal].enqueue(t, t->getPriority());
		else
			emptyTrucks[Normal].enqueue(t, t->getPriority());
	}
	file >> SpecialTruckCount;
	for (int i = 0; i < SpecialTruckCount; i++) {
		Truck* t = new SpecialTruck(file);
		if (t->getIsNightShift())
			NightTrucks[Special].enqueue(t, t->getPriority());
		else
			emptyTrucks[Special].enqueue(t, t->getPriority());
	}
	file >> VIPTruckCount;	
	for (int i = 0; i < VIPTruckCount; i++) {
		Truck* t = new VIPTruck(file);
		if (t->getIsNightShift())
			NightTrucks[VIP].enqueue(t, t->getPriority());
		else
			emptyTrucks[VIP].enqueue(t, t->getPriority());
	}

	

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


void Company::checkLoadingTrucks()
{
	
	/*
	* @Summary
	*   [BOOL]addLoadingTrucks Functions : Handeling Truck_Capacity &&  Max_Wait : and if could Load return True
	*	Calling addLoadingTrucks and send trucks with Assignment Order tell True or Options End
	*/
	//! ASSUME : that if there's no available Trucks First go Second or Third
	//! as mentiond below
	
	/* PriorityQueue ChoosenList */
	PriorityQueue<Truck*>* choosenList[3];
	for (int i = 0; i <= 2; i++) {
		if (emptyTrucks[i].isEmpty() || NightMode()) choosenList[i] = &NightTrucks[i];
		else if (NightTrucks[i].isEmpty()) choosenList[i] = &emptyTrucks[i];
		else if (NightTrucks[i].peekFront()->getPriority() < emptyTrucks[i].peekFront()->getPriority())
			choosenList[i] = &NightTrucks[i];
		else choosenList[i] = &emptyTrucks[i];
	}
	/* PriorityQueue ChoosenList */

	///1 - VIP Trucks
	if (!loadingTrucks.getEntry(VIP) && !waitingVIPCargo.isEmpty())
	{
		//get the min capcity of Any Suitable Truck according to assignment Rule
		int c = waitingVIPCargo.getSize();
		bool Now = waitingVIPCargo.peekFront()->MaxWCheck(currentTime, MaxW);

		//First: Check VIP Trucks
		for (int i = 0; i <= 2; i++) {
			if (!choosenList[Cargo_VIP_PRIORITY[i]]->isEmpty() && addLoadingTruck(choosenList[Cargo_VIP_PRIORITY[i]]->peekFront(), VIP, c, Now, choosenList[Cargo_VIP_PRIORITY[i]]))
				break;
		}
	}

	///2 - Special Trucks
	if (!loadingTrucks.getEntry(Special) && !choosenList[Special]->isEmpty() && !waitingSpecialCargo.isEmpty()){
		addLoadingTruck(choosenList[Special]->peekFront(), Special, waitingSpecialCargo.getSize(), waitingSpecialCargo.peekFront()->MaxWCheck(currentTime, MaxW), choosenList[Special]);
	}

	///3 - Normal Trucks
	if(!loadingTrucks.getEntry(Normal) && !waitingNormalCargo.isEmpty()){
		//get if cargo arrived Max Wait
		bool Now = waitingNormalCargo.getFront()->MaxWCheck(currentTime, MaxW);
		//get the min capcity of Any Suitable Truck according to assignment Rule
		int c = waitingNormalCargo.getSize();
		
		//check first Normal Empty Trucks
		for (int i = 0; i < 2; i++) {
			if (!choosenList[Cargo_NORMAL_PRIORITY[i]]->isEmpty() && addLoadingTruck(choosenList[Cargo_NORMAL_PRIORITY[i]]->peekFront(), Normal, c, Now, choosenList[Cargo_NORMAL_PRIORITY[i]]))
				break;
		}
	}

}
bool Company::addLoadingTruck(Truck * t, Types CargoType, int MinCapacity, bool Now, PriorityQueue<Truck *> * choosenTruckList)
{
	/*
	* @Summary
	*   [BOOL] Now : True means  MaxW Rule
	*	
	*/

	//1-Handeling if Truck Null
	if (!t) return false;
	//2-Handeling MaxW || Capacity
	if (Now || t->GetCapcity() <= MinCapacity) {
		//1-first Remove From empty Trucks
		choosenTruckList->dequeue();
		//2-inserted it in loading Trucks in position of 
		loadingTrucks.setEntry(CargoType, t);
		t->setNowMoving(Now);
		return true;
	}
	return false;
}
void Company::assign(bool isNight) {
	if (loadingTrucks.getEntry(Normal) && !waitingNormalCargo.isEmpty())
		if (loadingTrucks.getEntry(Normal)->AssignCargo(waitingNormalCargo.getFront(), currentTime, isNight))
		{   // changes to calculate the DI distance
			waitingNormalCargo.removeFront();
		}
	if (loadingTrucks.getEntry(Special) && !waitingSpecialCargo.isEmpty())
		if (loadingTrucks.getEntry(Special)->AssignCargo(waitingSpecialCargo.peekFront(), currentTime, isNight))
		{
			waitingSpecialCargo.dequeue();
		}

	if (loadingTrucks.getEntry(VIP) && !waitingVIPCargo.isEmpty())
		if (loadingTrucks.getEntry(VIP)->AssignCargo(waitingVIPCargo.peekFront(), currentTime, isNight))
		{
			waitingVIPCargo.dequeue();
		}
}



///////////////////////////////////////////////////MaxW

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
void Company::AddWaitingCargo(Cargo* temp)
{
	if (temp->getType() == VIP)
	{
		waitingVIPCargo.enqueue(temp, temp->getPriority());
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
void Company::DeliverCargos()
{
	PriorityQueue<Truck*>* aux = new PriorityQueue<Truck*>(getTotalTruckCount());
	while (!movingTrucks->isEmpty()) {
		//Handeling Loop
		Truck* t = movingTrucks->peekFront();
		movingTrucks->dequeue();
		
		t->Failuer(&currentTime, uiPtr);
		
		aux->enqueue(t, (t->GetDi() + t->GetMt()).ConvertToInt());

		///Handeling DeliverCargo One By One
		Cargo* c = t->DeliverCargos(currentTime);
		while (c) {
			if (t->getIsFailed())
				AddWaitingCargo(c);
			else
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
	return emptyTrucks[0].getSize() + emptyTrucks[1].getSize() + emptyTrucks[2].getSize();
}
int Company::getNightTrucksCount() const
{
	return NightTrucks[0].getSize() + NightTrucks[1].getSize() + NightTrucks[2].getSize();
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
const PriorityQueue<Truck*>* Company::getEmptyTrucks() const { return emptyTrucks; }
const PriorityQueue<Truck*>* Company::getNightTrucks() const{return NightTrucks;}
const List<Truck*>& Company::getLoadingTrucks() const { return loadingTrucks; }
const PriorityQueue< Truck*>* Company::getMovingTrucks() const { return movingTrucks; }
const Queue< Truck*>* Company::getMaintainingTrucks() const { return maintainingTrucks; }
////////////////////////Trucks
int Company::getTotalTruckCount() const
{
	return NormalTruckCount + SpecialTruckCount + VIPTruckCount;
}

bool Company::NightMode() const
{
	return currentTime.getHour() < 5 || currentTime.getHour() > 23;
}
Company::~Company() {
	delete movingTrucks;
	delete uiPtr;
}