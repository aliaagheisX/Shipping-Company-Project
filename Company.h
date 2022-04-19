#pragma once
#include<iostream>

class UI;
#include"VIPTruck.h"
#include"NormalTruck.h"
#include"SpecialTruck.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VIPCargo.h"
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
	List< Truck *> movingTrucks;
	List< Truck* > maintainingTrucks[3];

	LinkedList<NormalCargo*> waitingNormalCargo;
	Queue<SpecialCargo*> waitingSpecialCargo;
	PriorityQueue<VIPCargo*> waitingVIPCargo;

	UI *uiPtr;
public:
	Company() {
		uiPtr = new UI;
	}
	void load();
	void Print();
	LinkedList<NormalCargo*>& getWaitingNormalCargo(); // as we need to remove by id
	Queue<SpecialCargo*>& getWaitingSpecialCargo();
	PriorityQueue<VIPCargo*>& getWaitingVIPCargo();
};

