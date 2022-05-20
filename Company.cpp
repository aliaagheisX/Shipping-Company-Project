#include "Company.h"
#include "PreparationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include"UI.h"
#include<fstream>
#include<string>
using namespace std;

Company::Company() {
}

void Company::Simulate() {
	uiPtr = new UI;
	uiPtr->ReadMode();
	load();

	while (!isSimulationEnd())
	{
		
		
		if(currentTime.getHour() >= 5 && currentTime.getHour() <=23){
			ExecuteEvent();
			while (MaxwCheck(waitingNormalCargo.getFront()))
			{
				Cargo* temp = waitingNormalCargo.getFront();
				waitingNormalCargo.removeFront();
				AutoPromotion(temp);
			}
			while (MaxwCheck(waitingSpecialCargo.peekFront()))
			{
				Cargo* temp = waitingSpecialCargo.peekFront();
				waitingSpecialCargo.dequeue();
				AutoPromotion(temp);
			}
			//Max wait 
			//assign cargos
			uiPtr->Print(this);
		}
		else {
			//move trucks	
			//check moving trucks if they finish => waiting||checkup truck
			//truck finish checkups
			//deliverCargo
			//output
		}
			

		currentTime.Update();
	}
		//TODO: [statics]
}

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
bool Company::MaxwCheck(Cargo* c)
{
	return (currentTime.getDay() - c->GetPt().getDay() >= MaxW);
	
}
//void Company::DeliverCargos() {
//	if (!waitingVIPCargo.isEmpty()) {
//		waitingVIPCargo.peekFront()->setCDT(currentTime);
//		DeliveredCargos[VIP].enqueue(waitingVIPCargo.peekFront());
//		waitingVIPCargo.dequeue();
//	}
//	if (!waitingNormalCargo.isEmpty()) {
//
//		DeliveredCargos[Normal].enqueue(waitingNormalCargo[0]);
//		waitingNormalCargo.removeFront();
//	}
//	if (!waitingSpecialCargo.isEmpty()) {
//		DeliveredCargos[Special].enqueue(waitingSpecialCargo.peekFront());
//		waitingSpecialCargo.dequeue();
//	}
//}


void Company::ExecuteEvent() {
	while (!EventList.isEmpty() && currentTime == EventList.peekFront()->getEventTime())
	{
		EventList.peekFront()->Execute(this);
		EventList.dequeue();
	}

}

void Company::AutoPromotion(Cargo* c)
{
	c->setCargoType('V');
	getWaitingVIPCargo().enqueue(c, c->getPriority());
}

void Company::load()
{
	string path="Input_File.txt";
	ifstream file;

	file.open(path);

	file >> NormalTruckCount; 
	for (int i = 0; i < NormalTruckCount; i++) {
		emptyTrucks[Normal].enqueue(new NormalTruck);
	}
	file >> SpecialTruckCount;
	for (int i = 0; i < SpecialTruckCount; i++) {
		emptyTrucks[Special].enqueue( new SpecialTruck);
	}
	file >> VIPTruckCount;
	for (int i = 0; i < VIPTruckCount; i++) {
		emptyTrucks[VIP].enqueue(new VIPTruck);

	}
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

	file >> MaxW;
	file >> AutoP;

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
}

int Company::getWaitingCargosCount() const {

	return waitingNormalCargo.getSize() + waitingSpecialCargo.getSize() + waitingVIPCargo.getSize();
}
int Company::getEmptyTrucksCount() const {
	return emptyTrucks[Normal].getSize() + emptyTrucks[Special].getSize() + emptyTrucks[VIP].getSize();
}


int Company::getMovingCargosCount() const {
	/*int MovingCargoCount = 0;
	for (int i = 0; i < movingTrucks.getSize(); i++)
		MovingCargoCount += movingTrucks.getEntry(i)->getCargoList()->getSize();*/
	return MovingCargoCount;
}

int Company::getMaintainingTrucksCount() const {
	return maintainingTrucks[Normal].getSize() + maintainingTrucks[Special].getSize() + maintainingTrucks[VIP].getSize();
}

 const Time & Company::getCurrentTime() const {
	return currentTime;
}

 int Company::getDeliveredCargosCount() const { return DeliveredCargos.getSize(); }



LinkedList<Cargo*>& Company::getWaitingNormalCargo() {return waitingNormalCargo;}

Queue<Cargo*>& Company::getWaitingSpecialCargo() {return waitingSpecialCargo;}

PriorityQueue<Cargo*>& Company::getWaitingVIPCargo(){return waitingVIPCargo;}

Queue<int>& Company::getDeliveredCargo() { return DeliveredCargos; }




Queue<Truck*>* Company::getEmptyTrucks() { return emptyTrucks; }
PriorityQueue< Truck*>& Company::getMovingTrucks() { return movingTrucks; }
Queue< Truck*>* Company::getMaintainingTrucks() { return maintainingTrucks; }




Company::~Company() {
	while (!emptyTrucks->isEmpty()) emptyTrucks->dequeue();
}