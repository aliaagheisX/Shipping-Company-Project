#include "Company.h"
#include "PreparationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include"UI.h"
#include<fstream>
#include<string>
using namespace std;

Company::Company() {
	string IN_PATH = "Input_File.txt";
	string OUT_PATH="Output_File.txt";
	
}

void Company::Simulate() {
	uiPtr = new UI;
	uiPtr->ReadMode();
	load();

	Out_Start();
	while (!isSimulationEnd())
	{
		
		
		if(currentTime.getHour() >= 5 && currentTime.getHour() <=23){
			ExecuteEvent();
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
			Out_Mid();

		}
			

		currentTime.Update();
	}
			Out_End();
		//TODO: [statics]
}




void Company::Out_Start() {
	ofstream file;
	file.open(OUT_PATH);
	file << "CDT\tID\tPT\tWT\tTID\n";
	file.close();
}

void Company::Out_Mid() {
	ofstream file;
	file.open(OUT_PATH);
	while (!DeliveredCargos_temp.isEmpty()) {
		Cargo* temp = DeliveredCargos_temp.peekFront();
		DeliveredCargos.enqueue(temp->getID());
		DeliveredCargos_temp.dequeue();
		temp->getCDT().Out(file);
		file << '\t' << temp->getID() << '\t';
		temp->GetPt().Out(file);
		file << '\t';
		temp->GetWt().Out(file);
		file << '\t' << temp->getTID() << '\n';
	}
	file.close();
}

void Company::Out_End() {
	ofstream file;
	file.open(OUT_PATH);
	int TotalTrucksCount = NormalTruckCount + SpecialTruckCount + VIPTruckCount;
	file << ".........................................\n";
	file << ".........................................\n";
	file << "Cargos: " << DeliveredCargos.getSize() << "[N: "<<NormalCargoCount << ", S: " << SpecialCargoCount << ", V: " << VIPCargoCount  << "]";
	file << "\nCargo Avg Wait = "; CargoAvgWait.Out(file);
	file << "\nAuto-Promoted Cargos : " << PromotedCargoCount << "%\n";
	file << "Trucks: " << TotalTrucksCount << "[N: " << NormalTruckCount << ", S: " << SpecialTruckCount << ", V: " << VIPTruckCount << "]";
	file << "\nAvg Active Time = " << TotalTruckActiveTime / TotalTrucksCount * 100 << '%';
	file << "\nAvg utilization = " << TotalTruckUtilization / TotalTrucksCount * 100 << '\n';
	file.close();
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

void Company::load()
{
	ifstream file;

	file.open(IN_PATH);

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

void Company::assign()
{
	// vip cargo assignment 


	// 1st case assign in vip trucks 
	if (!emptyTrucks[VIP].isEmpty())
	{
		if (emptyTrucks[VIP].peekFront()->GetCapcity() <= waitingVIPCargo.getSize())
		{
			Truck* t = emptyTrucks[VIP].peekFront();

			for (int i = 0; i < t->GetCapcity(); i++)
			{
				Cargo* v = waitingVIPCargo.peekFront();
				waitingVIPCargo.dequeue();
				t->AssignCargo(v);
			}

			loadingTrucks.enqueue(t);
			emptyTrucks[VIP].dequeue();
		}
	}

	// 2nd case assign in normal trucks if there is no available vip trucks 
	if (emptyTrucks[VIP].isEmpty() && !emptyTrucks[Normal].isEmpty())
	{
		if (emptyTrucks[Normal].peekFront()->GetCapcity() <= waitingVIPCargo.getSize())
		{
			Truck* t = emptyTrucks[Normal].peekFront();

			for (int i = 0; i < t->GetCapcity(); i++)
			{
				Cargo* v = waitingVIPCargo.peekFront();
				waitingVIPCargo.dequeue();
				t->AssignCargo(v);
			}
			loadingTrucks.enqueue(t);
			emptyTrucks[Normal].dequeue();
		}
	}

	//3rd case assign in special trucks
	if (emptyTrucks[VIP].isEmpty() && emptyTrucks[Normal].isEmpty() && !emptyTrucks[Special].isEmpty())
	{
		if (emptyTrucks[Special].peekFront()->GetCapcity() <= waitingVIPCargo.getSize())
		{
			Truck* t = emptyTrucks[Special].peekFront();
			for (int i = 0; i < t->GetCapcity(); i++)
			{
				Cargo* v = waitingVIPCargo.peekFront();
				waitingVIPCargo.dequeue();
				t->AssignCargo(v);
			}
			loadingTrucks.enqueue(t);
			emptyTrucks[Special].dequeue();
		}
	}

	//! Asignment of special cargos
	if (!emptyTrucks[Special].isEmpty())
	{
		if (emptyTrucks[Special].peekFront()->GetCapcity() <= waitingSpecialCargo.getSize())
		{
			Truck* t = emptyTrucks[Special].peekFront();
			for (int i = 0; i < t->GetCapcity(); i++)
			{
				Cargo* v = waitingSpecialCargo.peekFront();
				waitingSpecialCargo.dequeue();
				t->AssignCargo(v);
			}
			loadingTrucks.enqueue(t);
			emptyTrucks[Special].dequeue();
		}
	}



	if (!emptyTrucks[Normal].isEmpty())
	{
		if (emptyTrucks[Normal].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
		{
			Truck* t = emptyTrucks[Normal].peekFront();
			for (int i = 0; i < t->GetCapcity(); i++)
			{
				Cargo* v = waitingNormalCargo.getFront();
				waitingNormalCargo.removeFront();
				t->AssignCargo(v);
			}
			loadingTrucks.enqueue(t);
			emptyTrucks[Normal].dequeue();
		}
	}

	if (emptyTrucks[Normal].isEmpty() && !emptyTrucks[VIP].isEmpty())
	{
		if (emptyTrucks[VIP].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
		{
			Truck* t = emptyTrucks[VIP].peekFront();
			for (int i = 0; i < t->GetCapcity(); i++)
			{
				Cargo* v = waitingNormalCargo.getFront();
				waitingNormalCargo.removeFront();
				t->AssignCargo(v);
			}
			loadingTrucks.enqueue(t);
			emptyTrucks[VIP].dequeue();
		}
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