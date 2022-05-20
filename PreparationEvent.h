#pragma once
#include"Event.h"
class PreparationEvent :public Event {
	char Types;
	int Distances;
	int LoadTime;
	int Cost;
public:
	virtual void Execute(Company* cPtr);
	virtual void Read(ifstream& InputFile);
};