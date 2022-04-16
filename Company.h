#pragma once
#include<iostream>
#include"VIPTruck.h"
#include"NormalTruck.h"
#include"SpecialTruck.h"
#include"Event.h"
#include"Queue.h"
class Company
{
	int NormalTruckCount, SpecialTruckCount, VIPTruckCount;
	int NormalCargoCount, SpecialCargoCount, VIPCargoCount;
	int MaxW, AutoP, J; // j no of journeys till maintaince

	int CargoAvgWait, PromotedCargoCount, TotalSimulationTime;
	Queue<Event *> EventList;

public:
	void load();
};

