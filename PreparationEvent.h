#pragma once
#include"Event.h"
class PreparationEvent :public Event {
	char CargoType;
	int Distances;
	int LoadTime;
	int Cost;
public:
	virtual void Execute(CargoList&);
	virtual void Read(ifstream& InputFile);
};