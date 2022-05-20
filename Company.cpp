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
}

void Company::Simulate() {
	uiPtr = new UI;
	uiPtr->ReadMode();
	load();

	Out_Start();
	while (!isSimulationEnd())
	{
		
		
			ExecuteEvent();
			AutoPromotion();
			//Max wait [Mahmoud]
			Out_Mid();
			//move trucks	[Ali]
			// 
			//check moving trucks if they finish => waiting||checkup truck[Mahmoud]
			//truck finish checkups [Mahmoud]
			// 
			//deliverCargo [Aliaa]
		if(currentTime.getHour() >= 5 && currentTime.getHour() <=23){
			checkLoadingTrucks();
			assign();
			uiPtr->Print(this);
		}
			

		currentTime.Update();
	}
	Out_End();
		//TODO: [statics]
}


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


void Company::Out_Start() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	file << "CDT\tID\tPT\tWT\tTID\n";
	file.close();
}
void Company::Out_Mid() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	while (!DeliveredCargos_temp.isEmpty()) {
		Cargo* temp = DeliveredCargos_temp.peekFront();
		DeliveredCargos.enqueue(temp->getID());
		DeliveredCargos_temp.dequeue();
		file << temp->getCDT().TimePrint();
		file << '\t' << temp->getID() << '\t' << temp->GetPt().TimePrint() << '\t' << temp->GetWt().TimePrint() << '\t' << temp->getTID() << '\n';
	}
	file.close();
}
void Company::Out_End() {
	ofstream file;
	file.open(OUT_PATH, std::ios_base::app);
	int TotalTrucksCount = NormalTruckCount + SpecialTruckCount + VIPTruckCount;
	file << ".........................................\n";
	file << ".........................................\n";
	file << "Cargos: " << DeliveredCargos.getSize() << "[N: "<<NormalCargoCount << ", S: " << SpecialCargoCount << ", V: " << VIPCargoCount  << "]";
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

void Company::addLoadingTruck(Types truckType, Types CargoType)
{
	Truck *t = emptyTrucks[truckType].peekFront();
	emptyTrucks[truckType].dequeue();
	loadingTrucks.setEntry(CargoType, t);
}
void Company::checkLoadingTrucks()
{
	// vip cargo assignment 


	// 1st case assign in vip trucks 
	if (!loadingTrucks.getEntry(VIP) )
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
	if (!loadingTrucks.getEntry(Special) && !emptyTrucks[Special].isEmpty() && emptyTrucks[Special].peekFront()->GetCapcity() <= waitingSpecialCargo.getSize())
		addLoadingTruck(Special, Special);


	if(!loadingTrucks.getEntry(Normal)){
		if (!emptyTrucks[Normal].isEmpty() && emptyTrucks[Normal].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
			addLoadingTruck(Normal, Normal);

		else if (emptyTrucks[Normal].isEmpty() && !emptyTrucks[VIP].isEmpty() && emptyTrucks[VIP].peekFront()->GetCapcity() <= waitingNormalCargo.getSize())
			addLoadingTruck(VIP, Normal);
	}

}

void Company::assign() {
	if (loadingTrucks.getEntry(Normal))
		if(loadingTrucks.getEntry(Normal)->AssignCargo(waitingNormalCargo.getFront(), currentTime))
			waitingNormalCargo.removeFront();

	if (loadingTrucks.getEntry(Special))
		if(loadingTrucks.getEntry(Special)->AssignCargo(waitingSpecialCargo.peekFront(), currentTime))
			waitingSpecialCargo.dequeue();

	if (loadingTrucks.getEntry(VIP))
		if(loadingTrucks.getEntry(VIP)->AssignCargo(waitingVIPCargo.peekFront(), currentTime))
			waitingVIPCargo.dequeue();
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

const Queue<int>& Company::getDeliveredCargo()const { return DeliveredCargos; }


const Queue<Truck*>* Company::getEmptyTrucks() const { return emptyTrucks; }
const List<Truck*>& Company::getLoadingTrucks() const { return loadingTrucks; }
const PriorityQueue< Truck*>& Company::getMovingTrucks() const { return movingTrucks; }
const Queue< Truck*>* Company::getMaintainingTrucks() const { return maintainingTrucks; }


Company::~Company() {
	while (!emptyTrucks->isEmpty()) emptyTrucks->dequeue();
}