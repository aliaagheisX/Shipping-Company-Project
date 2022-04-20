#pragma once
using namespace std;
#include <string>
#include "Time.h"
class Cargo
{   // Time Members in The Cargo
	Time PT; //prep. time 
	int LT; //loading time
	Time WT; //waiting time

	int CDT;

	const int ID;
	double DeliveryDist;

	double Cost;

public:
	Cargo(int);
	// Setters
	void SetPt(const Time& t); //trucl call it
	void SetLt(const int& t); //read from input
	void SetWt(const Time& t); //truck call = Truck::MT - PT
	void SetDeliveryDist(const int& dist);
	void SetCost(const int& ct);
	// Getters 
	const Time& GetPt() const;
	const Time& GetLt() const;
	const Time& GetWt() const;
	double GetDist() const;
	virtual double GetCost() const;


	const int getID() const;

	int getPriority() const { return 1; }

	//virtual bool operator<(const Cargo& r);
		// Waiting for the Priority Equation
	
};

