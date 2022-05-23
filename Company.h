#pragma once
#include<iostream>

class UI;
#include"VIPTruck.h"
#include"NormalTruck.h"
#include"SpecialTruck.h"
#include"Event.h"
#include"Time.h"
#include"Queue.h"
#include"Truck.h"
#include"List.h"

class Company
{
	int NormalTruckCount, SpecialTruckCount, VIPTruckCount;
	int NormalCargoCount, SpecialCargoCount, VIPCargoCount;
	int MaxW, AutoP, J; // j no of journeys till maintaince
	Time currentTime;

	//
	Time TotalCargoWait; 
	int TotalTruckActiveTime, PromotedCargoCount;double TotalTruckUtilization;
	
	int MovingCargoCount;

	Queue<Event *> EventList;

	Queue<Truck *> emptyTrucks [3];
	List<Truck *> loadingTrucks;
	PriorityQueue< Truck*>* movingTrucks;
	Queue<Truck *> maintainingTrucks[3];

	LinkedList<Cargo*> waitingNormalCargo;
	Queue<Cargo*> waitingSpecialCargo;
	PriorityQueue<Cargo*> waitingVIPCargo;

	Queue<int> DeliveredCargos[3];
	Queue<Cargo*> DeliveredCargos_temp;

	UI *uiPtr;


	bool isNightShift();

	void ExecuteEvent();
	//Loading
	void load();
	void assign();


	//moving
	void moveTrucks();
	void DeliverCargos();

	//checkups
	void EndCheckUP();
	bool isFinishedCheckUP(Truck* t);


	void AutoPromotion();
	bool AutoPCheck(Cargo *);

	bool CheckFailure(Truck* t);

	bool MaxWCheck(Cargo* c);
	void checkLoadingTrucks();
	void Promote(Cargo *);

	

	void addLoadingTruck(Types, Types);
	void EndSimulation();

	string IN_PATH;
	string OUT_PATH;
public:
	Company();
	void Simulate();
	void Movingcheck();
	bool isFinishedDelivery(Truck* t);
	inline bool NeedCheck(Truck* t);
	void Out_Mid();
	void Out_Start();
	void Out_End();
	bool isSimulationEnd();
	void Print() { uiPtr->Print(this); }
	//Getters

	int getWaitingCargosCount() const;
	int getMovingCargosCount() const;
	int getLoadingTrucksCount() const;
	int getEmptyTrucksCount() const;
	int getMaintainingTrucksCount() const;

	const Time& getCurrentTime() const;

	int getDeliveredCargosCount() const;


	LinkedList<Cargo*>& getWaitingNormalCargo(); // as we need to remove by id
	Queue<Cargo*>& getWaitingSpecialCargo();
	PriorityQueue<Cargo*>& getWaitingVIPCargo();


	const Queue<int>* getDeliveredCargo() const;

	const Queue<Truck*>* getEmptyTrucks() const;
	const List<Truck*>& getLoadingTrucks() const;
	const PriorityQueue< Truck*>* getMovingTrucks() const;
	const Queue< Truck*>* getMaintainingTrucks() const;
	
	~Company();
};