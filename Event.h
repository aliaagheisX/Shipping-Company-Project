#pragma once
#include"Time.h"
#include<fstream>
using namespace std;

class Company;

//Abstract Class for the Events

class Event
{
	Time EventTime;
	int CargoID;
public:

	virtual void Execute(Company * cPtr) = 0;
	virtual void Read(ifstream  & InputFile) = 0;
	//Getters
	int getId() const;
	const Time& getEventTime() const;

};

