#include "Company.h"
#include "PreparationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include"UI.h"
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
		emptyTrucks[Normal].insert(i, new NormalTruck);
	}
	file >> SpecialTruckCount;
	for (int i = 0; i < SpecialTruckCount; i++) {
		emptyTrucks[Special].insert(i, new SpecialTruck);
	}
	file >> VIPTruckCount;
	for (int i = 0; i < VIPTruckCount; i++) {
		emptyTrucks[VIP].insert(i, new VIPTruck);

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

	char open[3] = { '[', '(', '{' };
	char close[3] = { ']', ')', '}' };
	// Printing current Time in the Company
	uiPtr->Output("Current Time (Day:Hour)"+to_string(currentTime.getDay())+":"+ to_string(currentTime.getHour())+"\n");
	
	//Waiting Cargos:
	uiPtr->Output(
		to_string(waitingNormalCargo.getSize() + waitingSpecialCargo.getSize() + waitingVIPCargo.getSize()) 
		+ " Waiting Cargos: ["); 
	waitingNormalCargo.Print(uiPtr);
	uiPtr->Output("] (");
	waitingSpecialCargo.Print(uiPtr);
	uiPtr->Output(") {");
	waitingVIPCargo.Print(uiPtr);
	uiPtr->Output("}");
	uiPtr->Line();

	//emptyTrucks
	uiPtr->Output(
		to_string(emptyTrucks[Normal].getSize() + emptyTrucks[Special].getSize() + emptyTrucks[VIP].getSize())
		+ " Empty Trucks: [");
	emptyTrucks[Normal].Print(uiPtr);
	uiPtr->Output("] (");
	emptyTrucks[Special].Print(uiPtr);
	uiPtr->Output(") {");
	emptyTrucks[VIP].Print(uiPtr);
	uiPtr->Output("}");
	uiPtr->Line();

	// Moving Cargos
	int MovingCargoCount = 0;
	for (int i = 0; i < movingTrucks.getSize(); i++) 
		MovingCargoCount += movingTrucks.getEntry(i)->getCargoList().getSize();

	uiPtr->Output(to_string(MovingCargoCount) + " Moving Cargos: ");
	for (int i = 0; i < movingTrucks.getSize(); i++) {

		int getCargoType = movingTrucks.getEntry(i)->getCargoType();

		uiPtr->Output(to_string(movingTrucks.getEntry(i)->getID()) + open[getCargoType]);
		movingTrucks.getEntry(i)->getCargoList().Print(uiPtr);
		uiPtr->Output(close[getCargoType] + " ");

	}

	uiPtr->Line();

	//IN Check-up trucks
	uiPtr->Output(
		to_string(maintainingTrucks[Normal].getSize() + maintainingTrucks[Special].getSize() + maintainingTrucks[VIP].getSize())
		+ " In-Checkup Trucks: [");
	maintainingTrucks[Normal].Print(uiPtr);
	uiPtr->Output("] (");
	maintainingTrucks[Special].Print(uiPtr);
	uiPtr->Output(") {");
	maintainingTrucks[VIP].Print(uiPtr);
	uiPtr->Output("}");
	uiPtr->Line();
	
	
		
	uiPtr->Output("");
	
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
