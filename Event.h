#pragma once
#include"Time.h"
#include<fstream>
using namespace std;

class Company;

class Event
{
	Time EventTime;
	int CargoID;
public:
	virtual void Execute(Company * cPtr) = 0;
	virtual void Read(ifstream  & InputFile) = 0;
	int getId() const;

};

