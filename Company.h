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
	int CargoAvgWait, PromotedCargoCount, TotalSimulationTime;
	int MovingCargoCount;

	Queue<Event *> EventList;

	Queue<Truck *> emptyTrucks [3];
	PriorityQueue< Truck*> movingTrucks;
	Queue<Truck *> loadingTrucks;
	Queue<Truck *> maintainingTrucks[3];

	LinkedList<Cargo*> waitingNormalCargo;
	Queue<Cargo*> waitingSpecialCargo;
	PriorityQueue<Cargo*> waitingVIPCargo;

	Queue<int> DeliveredCargos;

	UI *uiPtr;


	bool isNightShift();
	void load();
	void assign();
	void ExecuteEvent();
	void DeliverCargos();
	void checkUP();
	void AutoPromotion();



public:
	Company();
	void Simulate();
	bool isSimulationEnd();
	void Print() { uiPtr->Print(this); }
	//Getters

	int getWaitingCargosCount() const;
	int getMovingCargosCount() const;
	int getEmptyTrucksCount() const;
	int getMaintainingTrucksCount() const;

	const Time& getCurrentTime() const;

	int getDeliveredCargosCount() const;


	LinkedList<Cargo*>& getWaitingNormalCargo(); // as we need to remove by id
	Queue<Cargo*>& getWaitingSpecialCargo();
	PriorityQueue<Cargo*>& getWaitingVIPCargo();


	Queue<int>& getDeliveredCargo();

	Queue<Truck*>* getEmptyTrucks();
	PriorityQueue< Truck*>& getMovingTrucks();
	Queue< Truck*>* getMaintainingTrucks();
	~Company();
};

