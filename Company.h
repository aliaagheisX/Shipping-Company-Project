#pragma once
#include"UI.h"
#include<iostream>
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

enum TruckType { Normal, Special, VIP };

class Company
{
	int NormalTruckCount, SpecialTruckCount, VIPTruckCount;
	int NormalCargoCount, SpecialCargoCount, VIPCargoCount;
	int MaxW, AutoP, J; // j no of journeys till maintaince
	Time currentTime;
	int CargoAvgWait, PromotedCargoCount, TotalSimulationTime;

	Queue<Event *> EventList;

	List< List<Truck*>*> emptyTrucks;
	List< Truck *> movingTrucks;
	List< Truck* > maintainingTrucks;

	List<NormalCargo*> waitingNormalCargo;
	Queue<SpecialCargo*> waitingSpecialCargo;
	PriorityQueue<VIPCargo*> waitingVIPCargo;

	UI *uiPtr;
public:
	Company() {
		uiPtr = new UI;
		emptyTrucks.insert(Normal, new List<Truck*>); //Normal
		emptyTrucks.insert(Special, new List<Truck*>); //Special
		emptyTrucks.insert(VIP, new List<Truck*>); //VIP
	}
	void load();
	void Print();
};

