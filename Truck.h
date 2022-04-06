#pragma once
#include "Time.h"
#include "PiorityQueue.h"
#include "Cargo.h"
class Truck
{
protected:
	static int counter;
	int ID;

	int DI; // delivery interval
	long J; // number of max journeys before maintainc
	PiorityQueue<Cargo*> loadedCargo; //cargos that assigned on truck
	Time MT; //Moving Time
	float& Speed;
	long& Capcity;

	long tDC; //total deliverid Cargos
	long tAT; //total active time

public:
	// constructor
	Truck(float& , long&);

	// Setters
	void SetJ(const long& j);

	void SetMt(const Time& t); //company call it and send the time when the truck start moving

	// Getters 
	int GetDi() const; // calculate the delivery interval and send it to company
	long GetJ() const; 
	const Time& GetMt() const; 
	float GetSpeed() const;
	long GetCapcity() const;

	//assign cargo to the Queue According to Distance
	virtual bool AssignCargo(Cargo* ) = 0;

	//check if there's cargo deleverid
	bool deliverCargo(Time* t);

};

