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
	//properties of similation
	Time currentTime;
	string IN_PATH;
	string OUT_PATH;
	ofstream out_file;
	UI* uiPtr;

	//counters
	int NormalTruckCount, SpecialTruckCount, VIPTruckCount; //count all trucks in company
	int MovingCargoCount;//count moving Cargos Count

	int MaxW, AutoP, J; // j no of journeys till maintaince
	
	
	//Types of Trucks By Priority of assignment of [Normal-VIP	] cargos
	const Types Cargo_VIP_PRIORITY[3] = { VIP, Normal, Special };
	const Types Cargo_NORMAL_PRIORITY[2] = { Normal, VIP };

	//Statitics
	Time TotalCargoWait; 
	int TotalTruckActiveTime, PromotedCargoCount;
	double TotalTruckUtilization;

	
	//..........................Lists..........................//
	Queue<Event *> EventList;

	//Trucks Lists
	//type of empty Trucks
	PriorityQueue<Truck *> emptyTrucks [3];
	PriorityQueue<Truck*> NightTrucks[3];
	
	List<Truck *> loadingTrucks;
	PriorityQueue< Truck*>* movingTrucks;
	Queue<Truck *> maintainingTrucks[3];

	//Cargos Lists
	LinkedList<Cargo*> waitingNormalCargo;
	Queue<Cargo*> waitingSpecialCargo;
	PriorityQueue<Cargo*> waitingVIPCargo;

	Queue<int> DeliveredCargos[3];
	Queue<Cargo*> DeliveredCargos_temp; //temp store cargos that delivered in this hour
										//to print it in OUTPUT_FILT.TXT
										//then store it's ID in DeliveredCargos according to it's type
										// to print it in UI
	//..........................Lists..........................//

	//..........................Function of Company..........................//
	bool NightMode() const;//bool to konw if Company not in working hours
	inline bool isSimulationEnd();//bool check if all trucks and cargos and events end
	void load();//call it in Constructor
				//read INPUT_FILE.txt 
				//Inialize all Data Read in .txt 
				//create new Trucks and pass input file to it

	void EndSimulation();
	void Out_End();

	void ExecuteEvent();

	//Loading Trucks & assign
	void assign(bool isNight = false);

	//void NightAddLoadTrucks();


	//moving
	void moveTrucks();
	void AddWaitingCargo(Cargo* temp);
	void DeliverCargos();

	//checkups
	void EndCheckUP();

	//Auto promotion
	void AutoPromotion();

	void Promote(Cargo *);


	//Trucks from move to checkUP || Empty
	void checkLoadingTrucks();
	bool addLoadingTruck(Truck* t, Types CargoType, int MinCapacity, bool Now, PriorityQueue<Truck*>* choosenTruckList);
	void TrucksReturnBack();

	//
	int getTotalTruckCount() const;
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