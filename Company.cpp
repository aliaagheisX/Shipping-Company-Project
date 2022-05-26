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
	 uiPtr = new UI;
	 int x;
	 x = uiPtr->Readmanual();
	 IN_PATH = "IN/Sample" + to_string(x) + ".txt";
	 OUT_PATH= "OUT/Output" + to_string(x) + ".txt";
	 load();
	//initalize IO & UI


	 //inialize Trucks
	 loadingTrucks.insert(Normal, NULL);
	 loadingTrucks.insert(Special, NULL);
	 loadingTrucks.insert(VIP, NULL);
	
	 movingTrucks = new PriorityQueue<Truck*>(getTotalTruckCount());
	 //inialize Trucks
	 
	 
	 //inialize Counters
	 TotalTruckActiveTime = TotalTruckUtilization = PromotedCargoCount = 0;

	 //inialize output file
	 out_file.open(OUT_PATH);
	 out_file << "CDT\tID\tPT\tWT\tTID\n";

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
			checkLoadingTrucks();
			assign(NightMode());
			uiPtr->Print(this);
		currentTime.Update();
	}
	EndSimulation();
}

// The conditions for continue of the simulation
inline bool Company::isSimulationEnd() {
	return  (
		EventList.isEmpty() &&
		waitingNormalCargo.isEmpty() &&
		waitingSpecialCargo.isEmpty() &&
		waitingVIPCargo.isEmpty() &&
		!getLoadingTrucksCount() &&
		movingTrucks->isEmpty() &&
		!getMaintainingTrucksCount()[NIGHT] &&
		!getMaintainingTrucksCount()[DAY] 
		);
}


//........................... Begin : [states of Trucks] Functions ...........................//

//when Trucks end their journey 
//Function Responsible for move Truck to [waiting | maintaing] Trucks [Day | Night]
void Company::TrucksReturnBack()
{
	//if Finished journey 
	while (!movingTrucks->isEmpty()&& movingTrucks->peekFront()->isFinishedDelivery(currentTime))
	{
		Truck* temp = movingTrucks->peekFront();
		//1- end journey
		temp->EndJourney(); // reset all journeies Properties for trucks
		
							
		//2- remove it from moveing
		movingTrucks->dequeue();

		//Get The Proper List To Add it to
		Types t= temp->getTruckType(); // to choose from [VIP | Special | Normal] Trucks

		// to choose from [maintaining | waiting] Trucks & [Day | Night]
		if (temp->CheckUP(currentTime, J,uiPtr))
			maintainingTrucks[temp->getIsNightShift()][t].enqueue(temp, temp->getFinishingCheckUPTime().ConvertToInt());
		else
			emptyTrucks[temp->getIsNightShift()][t].enqueue(temp, temp->getPriority());
	}
}

//loop through Trucks in checkup
//if it's finished loading move to waiting Trucks
void Company::EndCheckUP() {
	//loop through Truck_Modes [Day | Night]
	for(int Truck_MODE = DAY; Truck_MODE <= NIGHT;Truck_MODE++){
		//loop through Truck_Types [Normal | Special | VIP]
		for (int trucktype = Normal; trucktype <= VIP; trucktype++) {
			//loop for all finished check up
			while (!maintainingTrucks[Truck_MODE][trucktype].isEmpty() && maintainingTrucks[Truck_MODE][trucktype].peekFront()->isFinishedCheckUp(currentTime))
			{
				//if Finish Checkup
				Truck* t = maintainingTrucks[Truck_MODE][trucktype].peekFront();
				// 1-added 
				emptyTrucks[Truck_MODE][trucktype].enqueue(t, t->getPriority());
			
				t->endCheckUp();
			
				maintainingTrucks[Truck_MODE][trucktype].dequeue();
			}
		}
	}
}
///////////////////////////////////////////////////Change states of Trucks



///////////////////////////////////////////////////AutoP
void Company::AutoPromotion() {
	while (!waitingNormalCargo.isEmpty() && waitingNormalCargo.getFront()->AutoPCheck(currentTime, AutoP))
	{
		Cargo* c = waitingNormalCargo.getFront();
		c->setTypes('V');
		waitingNormalCargo.removeFront();
		waitingVIPCargo.enqueue(c, c->getPriority());
		PromotedCargoCount++;
	}
}



//........................... Begin : [Input|Output & End Simulation] Functions ...........................//
void Company::load()
{
	ifstream file;

	file.open(IN_PATH);

	file >> NormalTruckCount; 
	for (int i = 0; i < NormalTruckCount; i++) {
		Truck* t = new NormalTruck(file);
		emptyTrucks[t->getIsNightShift()][Normal].enqueue(t, t->getPriority());
	}
	file >> SpecialTruckCount;
	for (int i = 0; i < SpecialTruckCount; i++) {
		Truck* t = new SpecialTruck(file);
		emptyTrucks[t->getIsNightShift()][Special].enqueue(t, t->getPriority());
	}
	file >> VIPTruckCount;	
	for (int i = 0; i < VIPTruckCount; i++) {
		Truck* t = new VIPTruck(file);
		emptyTrucks[t->getIsNightShift()][VIP].enqueue(t, t->getPriority());
	}

	
	file >> J;

	int CheckUPTime;

	file >> CheckUPTime;
	NormalTruck::setCheckUPTime(CheckUPTime);

	file >> CheckUPTime;
	SpecialTruck::setCheckUPTime(CheckUPTime);

	file >> CheckUPTime;
	VIPTruck::setCheckUPTime(CheckUPTime);


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


void Company::EndSimulation(){
	/*
	* @Summary
	* looping on the (empty & night) trucks to calculate the Total truck active time
	* and the total truck utilization 
	*/
	for(int Truck_Mode = DAY;Truck_Mode <= NIGHT;Truck_Mode++)
		for(int Truck_Type = Normal; Truck_Type <= VIP; Truck_Type++){
			while (!emptyTrucks[Truck_Mode][Truck_Type].isEmpty()) {
				Truck* t = emptyTrucks[Truck_Mode][Truck_Type].peekFront();
				TotalTruckActiveTime += t->getTotalActiveTime();
				TotalTruckUtilization += t->getTruckUtilization(currentTime);
				emptyTrucks[Truck_Mode][Truck_Type].dequeue();
			}
	}

	Out_End();
	
}
void Company::Out_End() {
	int AvgCargoWait = getDeliveredCargosCount() == 0 ? 0 : TotalCargoWait.ConvertToInt() / getDeliveredCargosCount();
	
	double AvgPromotedCargo = getDeliveredCargosCount() == 0 ? 0 : (double)PromotedCargoCount / getDeliveredCargosCount() * 100;
	
	double AvgActiveTime = ((double)currentTime.ConvertToInt() * getTotalTruckCount()) == 0 ? 0: TotalTruckActiveTime / ((double)currentTime.ConvertToInt() * getTotalTruckCount()) * 100;
	
	double AvgTruckUtilization = getTotalTruckCount() == 0 ? 0 : TotalTruckUtilization / getTotalTruckCount() * 100;
	
	
	out_file << ".........................................\n";
	out_file << ".........................................\n";
	out_file << "Cargos: " << getDeliveredCargosCount() << "[N: " << DeliveredCargos[0].getSize() << ", S: " << DeliveredCargos[1].getSize() << ", V: " << DeliveredCargos[2].getSize() << "]";
	out_file << "\nCargo Avg Wait = " << Time(0, AvgCargoWait).TimePrint();
	out_file << "\nAuto-Promoted Cargos : " << AvgPromotedCargo  << "%\n";
	out_file << "Trucks: " << getTotalTruckCount() << "[N: " << NormalTruckCount << ", S: " << SpecialTruckCount << ", V: " << VIPTruckCount << "]";
	out_file << "\nAvg Active Time = " << AvgActiveTime << '%';
	out_file << "\nAvg utilization = " << AvgTruckUtilization << "%\n";

}
//........................... Begin : [Input|Output & End Simulation] Functions ...........................//



void Company::ExecuteEvent() {

	/*
	* @Summary
	*   cheking if there is an event and the execution time has come
	*	then executing the event delete it and dequeue
	*/
	while (!EventList.isEmpty() && currentTime == EventList.peekFront()->getEventTime())
	{
		EventList.peekFront()->Execute(this);
		delete EventList.peekFront();
		EventList.dequeue();
	}

}

//........................... Begin : [Loading & Assign] Functions ...........................//
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
	PriorityQueue<Truck*>* backup[3];
	for (int i = 0; i <= 2; i++) {
		//choose waiting emptyTrucks [Night ||| DAY]
		if (emptyTrucks[DAY][i].isEmpty() || NightMode()) choosenList[i] = &emptyTrucks[NIGHT][i];

		else if (emptyTrucks[NIGHT][i].isEmpty()) choosenList[i] = &emptyTrucks[DAY][i];

		else if (emptyTrucks[NIGHT][i].peekFront()->getPriority() < emptyTrucks[DAY][i].peekFront()->getPriority())
			choosenList[i] = &emptyTrucks[NIGHT][i];
		else choosenList[i] = &emptyTrucks[DAY][i];
	

		//choose backup from maintaing Trucks [Night ||| DAY]
		if (maintainingTrucks[DAY][i].isEmpty() || NightMode()) backup[i] = &maintainingTrucks[NIGHT][i];

		else if (maintainingTrucks[NIGHT][i].isEmpty()) backup[i] = &maintainingTrucks[DAY][i];

		else if (maintainingTrucks[NIGHT][i].peekFront()->getPriority() < maintainingTrucks[DAY][i].peekFront()->getPriority())
			backup[i] = &maintainingTrucks[NIGHT][i];
		else backup[i] = &maintainingTrucks[DAY][i];
		
		//if (NightMode() || emptyTrucks[DAY][i].isEmpty()) {
		//	if (emptyTrucks[NIGHT][i].isEmpty())
		//		choosenList[i] = &maintainingTrucks[NightMode()][i];
		//	else
		//		choosenList[i] = &emptyTrucks[NIGHT][i];
		//}
		//else if (emptyTrucks[NIGHT][i].isEmpty() && emptyTrucks[DAY][i].isEmpty()) {
		//	if (maintainingTrucks[NIGHT][i].peekFront()->getPriority() < maintainingTrucks[DAY][i].peekFront()->getPriority())
		//		choosenList[i] = &maintainingTrucks[NIGHT][i];
		//	else choosenList[i] = &maintainingTrucks[DAY][i];
		//}

		/*if (!NightMode()) {
			if (getEmptyTrucksCount()[0] + getEmptyTrucksCount()[1] == 0) {
				if (maintainingTrucks[NIGHT][i].isEmpty()) choosenList[i] = &maintainingTrucks[DAY][i];
				else if (maintainingTrucks[DAY][i].isEmpty())choosenList[i] = &maintainingTrucks[NIGHT][i];
				else if (maintainingTrucks[NIGHT][i].peekFront()->getPriority() < maintainingTrucks[DAY][i].peekFront()->getPriority())
					choosenList[i] = &maintainingTrucks[NIGHT][i];
				else choosenList[i] = &maintainingTrucks[DAY][i];
				
				if (!choosenList[i]->isEmpty())
				{
					Truck* t = choosenList[i]->peekFront();
					uiPtr->Output("Bonus The company need this truck ID: " +to_string(t->getID()) + " " + " The speed :" + to_string(t->GetSpeed()));
					t->SetSpeed(choosenList[i]->peekFront()->GetSpeed() / 2);
					uiPtr->Output("\nThen became :" + to_string(t->GetSpeed()));
				}

			}

			else {
				if (emptyTrucks[NIGHT][i].isEmpty()) choosenList[i] = &emptyTrucks[DAY][i];
				else if (emptyTrucks[DAY][i].isEmpty())choosenList[i] = &emptyTrucks[NIGHT][i];
				else if (emptyTrucks[NIGHT][i].peekFront()->getPriority() < emptyTrucks[DAY][i].peekFront()->getPriority())
					choosenList[i] = &emptyTrucks[NIGHT][i];
				else choosenList[i] = &emptyTrucks[DAY][i];
			}
		}
		else {
			if (getEmptyTrucksCount()[DAY] + getEmptyTrucksCount()[NIGHT] == 0){
				choosenList[i] = &maintainingTrucks[NIGHT][i];
				if (!choosenList[i]->isEmpty())
				{
					Truck* t = choosenList[i]->peekFront();
					uiPtr->Output("Bonus The company need this truck ID: " + to_string(t->getID()) + " " + " The speed :" + to_string(t->GetSpeed()));
					t->SetSpeed(choosenList[i]->peekFront()->GetSpeed() / 2);
					uiPtr->Output("\nThen became :" + to_string(t->GetSpeed()));
				}
			}
			else
				choosenList[i] = &emptyTrucks[NIGHT][i];

		}
	}*/
	/* PriorityQueue ChoosenList */

	///1 - VIP Trucks
	if (!loadingTrucks.getEntry(VIP) && !waitingVIPCargo.isEmpty())
	{
		//get the min capcity of Any Suitable Truck according to assignment Rule
		int c = waitingVIPCargo.getSize();
		bool Now = waitingVIPCargo.peekFront()->MaxWCheck(currentTime, MaxW);

		//Loop Through Priorities Trucks Types of Cargos VIP  Cargo_VIP_PRIORITY[VIP => Normal => Special]
		int Truck_Type = 0; //
		for (; i <= 2; i++) {
			if (!choosenList[Cargo_VIP_PRIORITY[Truck_Type]]->isEmpty() && addLoadingTruck(choosenList[Cargo_VIP_PRIORITY[Truck_Type]]->peekFront(), VIP, c, Now, choosenList[Cargo_VIP_PRIORITY[Truck_Type]]))
				break;
		}
		//if fail to load on Empty Trucks 
		//Try BackUP
		if (i == 3) {
			for (int i = 0; i <= 2; i++) {
				if (!backup[Cargo_VIP_PRIORITY[i]]->isEmpty() && addLoadingTruck(backup[Cargo_VIP_PRIORITY[i]]->peekFront(), VIP, c, Now, backup[Cargo_VIP_PRIORITY[i]])) {
					Truck* t = backup[i]->peekFront();
					uiPtr->Output("Bonus The company need this truck ID: " + to_string(t->getID()) + " " + " The speed :" + to_string(t->GetSpeed()));
					t->SetSpeed(choosenList[i]->peekFront()->GetSpeed() / 2);
					uiPtr->Output("\nThen became :" + to_string(t->GetSpeed()));
					break;
				}
					
			}
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
		int i = 0;
		for (; i < 2; i++) {
			if (!choosenList[Cargo_NORMAL_PRIORITY[i]]->isEmpty() && addLoadingTruck(choosenList[Cargo_NORMAL_PRIORITY[i]]->peekFront(), Normal, c, Now, choosenList[Cargo_NORMAL_PRIORITY[i]]))
				break;
		}
		if (i == 2) {
			for(int j = 0;j < 2;j++){
				if (!choosenList[Cargo_NORMAL_PRIORITY[j]]->isEmpty() && addLoadingTruck(choosenList[Cargo_NORMAL_PRIORITY[j]]->peekFront(), Normal, c, Now, choosenList[Cargo_NORMAL_PRIORITY[j]])) {
					Truck* t = backup[i]->peekFront();
					uiPtr->Output("Bonus The company need this truck ID: " + to_string(t->getID()) + " " + " The speed :" + to_string(t->GetSpeed()));
					t->SetSpeed(choosenList[i]->peekFront()->GetSpeed() / 2);
					uiPtr->Output("\nThen became :" + to_string(t->GetSpeed()));
					break;
				}
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
//........................... End : [Loading & Assign] Functions ...........................//



//........................... Begin : [Move & Deliver Cargos] Functions ...........................//
void Company::moveTrucks()
{
	/*
	* @Summary
	*   moveTrucks: making a for loop in the loading trucks
	*  if the truck is able to move by the move function in side the truck
	*  then remove it from the loading trucks and put it in the moving trucks
	*  increase the moving cargo count
	*/

	for (int i = 0; i < loadingTrucks.getSize(); i++) {
		Truck* t = loadingTrucks.getEntry(i);
		if ( t && t->move(&currentTime)) {
			loadingTrucks.setEntry(i, NULL);

			movingTrucks->enqueue(t, (t->GetDi() + t->GetMt()).ConvertToInt());
			MovingCargoCount += t->getCargoList()->getSize();
		}
	}
}

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
	/*
	* @Summary
	*   making auxiliary Pqueue of trucks
	*   taking the truck from the moving truk Pqueue
	*	calling failuer function
	*   and put the truck in the auxiliary Pqueue
	*	handelling the 
	and add cargo to waiting 
	*   or Dliver the cargo and update the Total cargo time
	*/

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
			else {
				DeliveredCargos[c->getType()].enqueue(c->getID());
				c->output(out_file);
				TotalCargoWait = TotalCargoWait + c->GetWt();
				delete c;
			}
			
			MovingCargoCount--;
			c = t->DeliverCargos(currentTime);
		}

	}
	
	delete movingTrucks;
	movingTrucks = aux;
}
//........................... End : [Move & Deliver Cargos] Functions ...........................//



//........................... Start : [Simulation Properties Getters] Functions ...........................//
const Time & Company::getCurrentTime() const {
	return currentTime;
}
bool Company::NightMode() const
{
	return currentTime.getHour() < 5 || currentTime.getHour() > 23;
}
//........................... Start : [Simulation Properties Getters] Functions ...........................//




//........................... Start : [Counters Getters] Functions ...........................//
int Company::getWaitingCargosCount() const {

	return waitingNormalCargo.getSize() + waitingSpecialCargo.getSize() + waitingVIPCargo.getSize();
}
int* Company::getEmptyTrucksCount() const {
	int arr[2] =
	{ emptyTrucks[DAY][Normal].getSize() + emptyTrucks[DAY][Special].getSize() + emptyTrucks[DAY][VIP].getSize()
		, emptyTrucks[NIGHT][Normal].getSize() + emptyTrucks[NIGHT][Special].getSize() + emptyTrucks[NIGHT][VIP].getSize() };
	return arr;
}
int Company::getNightTrucksCount() const
{
	return emptyTrucks[NIGHT][0].getSize() + emptyTrucks[NIGHT][1].getSize() + emptyTrucks[NIGHT][2].getSize();
}
int Company::getMovingCargosCount() const { return MovingCargoCount;}
int Company::getLoadingTrucksCount() const { 
	int count = 0;
	for (int i = 0; i <= VIP; i++)
		count+= bool(loadingTrucks.getEntry(i));
	return count;
}
int* Company::getMaintainingTrucksCount() const {
	int arr[2] =
	{ maintainingTrucks[DAY][Normal].getSize() + maintainingTrucks[DAY][Special].getSize() + maintainingTrucks[DAY][VIP].getSize()
		, maintainingTrucks[NIGHT][Normal].getSize() + maintainingTrucks[NIGHT][Special].getSize() + maintainingTrucks[NIGHT][VIP].getSize() };
	return arr;
}
int Company::getDeliveredCargosCount() const { return DeliveredCargos[0].getSize() + DeliveredCargos[1].getSize() + DeliveredCargos[2].getSize(); }
int Company::getTotalTruckCount() const
{
	return NormalTruckCount + SpecialTruckCount + VIPTruckCount;
}
//........................... End : [Counters Getters] Functions ...........................//



//........................... Start : [Cargos Getters] Functions ...........................//
 LinkedList<Cargo*>& Company::getWaitingNormalCargo() {return waitingNormalCargo;}
 Queue<Cargo*>& Company::getWaitingSpecialCargo() {return waitingSpecialCargo;}
 PriorityQueue<Cargo*>& Company::getWaitingVIPCargo()
 {return waitingVIPCargo;}
const Queue<int>* Company::getDeliveredCargo()const { return DeliveredCargos; }
//........................... End : [Cargos Getters] Functions ...........................//


//........................... Start : [Trucks Getters] Functions ...........................//
const PriorityQueue<Truck*>* Company::getEmptyTrucks(int Truck_Mode) const {

	switch (Truck_Mode)
	{
	case DAY:
		return emptyTrucks[DAY];
		break;
	default:
		return emptyTrucks[NIGHT];
		break;
	}
}
const PriorityQueue<Truck*>* Company::getNightTrucks() const{return emptyTrucks[NIGHT]; }
const List<Truck*>& Company::getLoadingTrucks() const { return loadingTrucks; }
const PriorityQueue< Truck*>* Company::getMovingTrucks() const { return movingTrucks; }
const PriorityQueue< Truck*>* Company::getMaintainingTrucks (int Truck_Mode) const{ 

	switch (Truck_Mode)
	{
		case DAY: 
			return maintainingTrucks[DAY];
			break;
		default:
			return maintainingTrucks[NIGHT];
			break;
	}
}
//........................... End : [Trucks Getters] Functions ...........................//


Company::~Company() {
	out_file.close();
	delete movingTrucks;
	delete uiPtr;
}