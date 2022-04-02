#pragma once
#include "Time.h"
class Cargo
{   // Time Members in The Cargo
	Time PT; //prep. time 
	Time LT; //loading time
	Time WT; //waiting time

	int CDT;

	double DeliveryDist;
	double Cost;

public:

	// Setters
	void SetPt(const Time& t); //trucl call it
	void SetLt(const Time& t); //read from input
	void SetWt(const Time& t); //truck call = Truck::MT - PT
	void SetDeliveryDist(const long& dist);
	void SetCost(const long& ct);
	// Getters 
	const Time& GetPt() const;
	const Time& GetLt() const;
	const Time& GetWt() const;
	double GetDist() const;

	virtual double GetCost() const;
};

