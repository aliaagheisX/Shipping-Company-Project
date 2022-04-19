#include "Company.h"
#include "PreparationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include<fstream>
#include<string>


using namespace std;
void Company::load()
{
	string path="Input_File.txt";
	ifstream file;

	file.open(path);

	file >> NormalTruckCount; 
	for (int i = 0; i < NormalTruckCount; i++) {
		emptyTrucks.getEntry(Normal)->insert(i, new NormalTruck);
	}
	file >> SpecialTruckCount;
	for (int i = 0; i < SpecialTruckCount; i++) {
		emptyTrucks.getEntry(Special)->insert(i, new SpecialTruck);
	}
	file >> VIPTruckCount;
	for (int i = 0; i < VIPTruckCount; i++) {
		emptyTrucks.getEntry(VIP)->insert(i, new VIPTruck);
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

void Company::Print()
{
	
	// Printing current Time in the Company
	uiPtr->Output("Current Time (Day:Hour)"+to_string(currentTime.getDay())+":"+ to_string(currentTime.getHour())+"\n");

	uiPtr->Output(to_string(waitingNormalCargo.getSize() + waitingSpecialCargo.getSize() + waitingVIPCargo.getSize()) + " Waiting Cargos: ");
	for (int i = 0; i < waitingNormalCargo.getSize(); i++){
		//uiPtr->Output();
	}	
	uiPtr->Output(" ");
	
}

LinkedList<NormalCargo*>& Company::getWaitingNormalCargo()
{
	return waitingNormalCargo;
}

Queue<SpecialCargo*>& Company::getWaitingSpecialCargo()
{
	return waitingSpecialCargo;
}

PriorityQueue<VIPCargo*>& Company::getWaitingVIPCargo()
{
	return waitingVIPCargo;
}
