#pragma once
using namespace std;
#include <string>
#include "Truck.h"
#include "Time.h"
class Cargo
{   // Time Members in The Cargo
	Time PT; //prep. time 
	int LT; //loading time	
	Time WT; //waiting time
	Time CDT;
	char types;

	const int ID;
	int DeliveryDist;

	const Truck* Loadingtrcuk;

	int Cost;

public:
	Cargo(int i, char c, int Dst, int cst, int L,Time t);
	//Cargo(int, char);
	// Setters
	void SetPt(const Time& t); //truck call it
	void SetLt(const int& t); //read from input
	void SetWt(const Time& t); //truck call = Truck::MT - PT
	void SetStart(const Time& t); /// time the cargo assigned
	void SetDeliveryDist(const int& dist);
	void SetCost(const int& ct);
	void setCDT(const Time&);
	void setTypes(char c);
	void setLoadingTruck(const Truck *);
	// Getters 
	const Time& GetPt() const;
	const int GetLt() const;
	const Time& GetWt() const;
	const Time& getCDT() const;
	const Time& GetStart() const;
	int GetDist() const;

	virtual int GetCost() const;
	int getType() const { 
		if (types == 'N') return 0; 
		if (types == 'V') return 2; 
		return 1; 
	}
	const Truck* getLoadingTruck() const;

	const int getID() const;

	int getPriority() const;


	void Deliver();
	//virtual bool operator<(const Cargo& r);
		// Waiting for the Priority Equation
	
};

