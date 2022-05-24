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

	string IN_PATH;
	string OUT_PATH;
	UI *uiPtr;

	//bool isNightShift();

	void load();
	void Out_Start();
	void ExecuteEvent();

	//Loading Trucks & assign
	bool addLoadingTruck(Truck *, Types, int MinCapacity, bool Now = false);
	void assign();


	//moving
	void moveTrucks();
	void DeliverCargos();

	//checkups
	void EndCheckUP();
	bool isFinishedCheckUP(Truck* t);

	//Auto promotion
	void AutoPromotion();
	inline bool AutoPCheck(Cargo *);
	void Promote(Cargo *);

	//Max wait
	inline bool MaxWCheck(Cargo* c);

	//Trucks from move to checkUP || Empty
	void checkLoadingTrucks();
	void Movingcheck();
	bool isFinishedDelivery(Truck* t);
	inline bool NeedCheck(Truck* t);

	bool CheckFailure(Truck* t);


	void Out_Mid();

	inline bool isSimulationEnd();
	void EndSimulation();
	void Out_End();

	
public:
	Company();
	void Simulate();


	//Getters
	int getWaitingCargosCount() const;
	int getMovingCargosCount() const;
	int getLoadingTrucksCount() const;
	int getEmptyTrucksCount() const;
	int getMaintainingTrucksCount() const;
	int getDeliveredCargosCount() const;

	const Time& getCurrentTime() const;


	//Getters Of Cargos
	 LinkedList<Cargo*>& getWaitingNormalCargo();
	 Queue<Cargo*>& getWaitingSpecialCargo();
	 PriorityQueue<Cargo*>& getWaitingVIPCargo();
	const Queue<int>* getDeliveredCargo() const;


	const Queue<Truck*>* getEmptyTrucks() const;
	const List<Truck*>& getLoadingTrucks() const;
	const PriorityQueue< Truck*>* getMovingTrucks() const;
	const Queue< Truck*>* getMaintainingTrucks() const;
	
	~Company();
};