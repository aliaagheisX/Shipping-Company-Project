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
	Time CDT; // cargo delivery time
	char types; 

	const int ID; 
	int DeliveryDist; 

	const Truck* Loadingtrcuk; 

	int Cost;

public:
	// constructor
	//inialize all data
	Cargo(int i, char c, int Dst, int cst, int L,Time t);

	//.......... Setters...........//
	void SetPt(const Time& t); //truck call it
	void SetLt(const int& t); //read from input
	void SetWt(const Time& t); //truck call = Truck::MT - PT
	void SetDeliveryDist(const int& dist); // 
	void SetCost(const int& ct);
	void setCDT(const Time&);
	void setTypes(char c);
	void setLoadingTruck(const Truck *); // setting the holding truck
	//......... Getters .........//
	
	//Get Time
	const Time& GetPt() const;
	const int GetLt() const;
	const Time& GetWt() const;
	const Time& getCDT() const;

	//Get Cargo Properties
	int GetCost() const;
	int GetDist() const;
	int getType() const;
	const int getID() const;
	int getPriority() const;
	const Truck* getLoadingTruck() const;

	//Get Checkers
	bool AutoPCheck(const Time & currentTime, int  AutoP) const; // checking the Auto-promotion
	bool MaxWCheck(const Time & currentTime, int MaxW)const; //checking the Maximum weight

	//Output
	void output(ofstream&) const;
	
};

