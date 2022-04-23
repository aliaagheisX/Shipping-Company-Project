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
	List<Truck *> loadingTrucks[3];
	Queue<Truck *> maintainingTrucks[3];

	LinkedList<Cargo*> waitingNormalCargo;
	Queue<Cargo*> waitingSpecialCargo;
	PriorityQueue<Cargo*> waitingVIPCargo;

	Queue<Cargo*> DeliveredCargos[3];

	UI *uiPtr;
	void load();
	void ExecuteEvent();
	// functions to setup
	void assign();
	void checkUP();
	void AutoPromotion();
	void OutputFile();
	void OutputCargo(int cargotype, ofstream file);
public:
	Company();
	void Simulate();
	void Print() { uiPtr->Print(this); }
	//Getters

	int getWaitingCargosCount() const;
	int getMovingCargosCount() const;
	int getEmptyTrucksCount() const;
	int getMaintainingTrucksCount() const;

	const Time& getCurrentTime() const;

	int getDeliveredCargosCount() const;


	LinkedList<Cargo*>& getWaitingNormalCargo(); // As we need to remove by Id
	Queue<Cargo*>& getWaitingSpecialCargo();
	PriorityQueue<Cargo*>& getWaitingVIPCargo();


	Queue<Cargo*>* getDeliveredCargo();

	Queue<Truck*>* getEmptyTrucks();
	PriorityQueue< Truck*>& getMovingTrucks();
	Queue< Truck*>* getMaintainingTrucks();

};

