#pragma once
#include"Time.h"
#include "CargoList.h"
#include<fstream>
using namespace std;
class Event
{
	Time EventTime;
	int CargoID;
public:
	virtual void Execute(CargoList&) = 0;
	virtual void Read(ifstream  & InputFile) = 0;
};

