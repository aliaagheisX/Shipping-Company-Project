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

	PriorityQueue<Truck *> emptyTrucks [3];
	PriorityQueue<Truck*> NightTrucks[3];
	
	const Types Cargo_VIP_PRIORITY[3] = { VIP, Normal, Special };
	const Types Cargo_NORMAL_PRIORITY[2] = { Normal, VIP };

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
	//

	Types priority_VIP_cargos[3] = {VIP, Normal, Special};
	//bool isNightShift();

	void load();
	void Out_Start();
	void ExecuteEvent();

	//Loading Trucks & assign
	bool addLoadingTruck(Truck *, Types, int MinCapacity, bool Now = false);
	void assign(bool isNight = false);

	//void NightAddLoadTrucks();


	//moving
	void moveTrucks();
	void DeliverCargos();

	//checkups
	void EndCheckUP();

	//Auto promotion
	void AutoPromotion();

	void Promote(Cargo *);


	//int getMinCapacity(Types CargoType) const;

	void AddWaitingCargo(Cargo* temp);

	//Max wait
	inline bool MaxWCheck(Cargo* c);

	//Trucks from move to checkUP || Empty
	void checkLoadingTrucks();
	bool addLoadingTruck(Truck* t, Types CargoType, int MinCapacity, bool Now, PriorityQueue<Truck*>* choosenTruckList);
	void TrucksReturnBack();

	void Out_Mid();

	inline bool isSimulationEnd();
	void EndSimulation();
	void Out_End();




	//
	int getTotalTruckCount() const;
	bool NightMode() const;
public:
	Company();
	void Simulate();


	//Getters
	int getWaitingCargosCount() const;
	int getMovingCargosCount() const;
	int getLoadingTrucksCount() const;
	int getEmptyTrucksCount() const;
	int getNightTrucksCount() const;
	int getMaintainingTrucksCount() const;
	int getDeliveredCargosCount() const;

	const Time& getCurrentTime() const;


	//Getters Of Cargos
	 LinkedList<Cargo*>& getWaitingNormalCargo();
	 Queue<Cargo*>& getWaitingSpecialCargo();
	 PriorityQueue<Cargo*>& getWaitingVIPCargo();
	const Queue<int>* getDeliveredCargo() const;


	const PriorityQueue<Truck*>* getEmptyTrucks() const;
	const PriorityQueue<Truck*>* getNightTrucks() const;
	const List<Truck*>& getLoadingTrucks() const;
	const PriorityQueue< Truck*>* getMovingTrucks() const;
	const Queue< Truck*>* getMaintainingTrucks() const;
	
	~Company();
};