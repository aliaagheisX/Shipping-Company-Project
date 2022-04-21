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

	Queue<Event *> EventList;

	List<Truck*> emptyTrucks [3];
	List< Truck*> movingTrucks;
	List< Truck *> loadingTrucks;
	List< Truck* > maintainingTrucks[3];

	LinkedList<Cargo*> waitingNormalCargo;
	Queue<Cargo*> waitingSpecialCargo;
	PriorityQueue<Cargo*> waitingVIPCargo;

	List<Cargo*> DeliveredCargos[3];

	UI *uiPtr;
	void load();
	void ExecuteEvent();
public:

	void Simulate();
	void Print() { uiPtr->Print(this); }
	//Getters

	int getWaitingCargosCount() const;
	int getMovingCargosCount() const;
	int getEmptyTrucksCount() const;
	int getMaintainingTrucksCount() const;

	Time& getCurrentTime() const;

	int getDeliveredCargosCount() const;
	const Time& getCurrentTime() const;


	LinkedList<Cargo*>& getWaitingNormalCargo(); // as we need to remove by id
	Queue<Cargo*>& getWaitingSpecialCargo();
	PriorityQueue<Cargo*>& getWaitingVIPCargo();


	List<Cargo*>* getDeliveredCargo();

	List<Truck*>* getEmptyTrucks();
	List< Truck*>& getMovingTrucks();
	List< Truck*>* getMaintainingTrucks();

};

