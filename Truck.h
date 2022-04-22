#pragma once
#include "Time.h"
#include "PriorityQueue.h"
#include "Cargo.h"
enum CargoType {Normal, Special, VIP  };
class Truck
{
protected:
	static int counter;
	int ID;
	
	int DI; // delivery interval
	PriorityQueue<Cargo*> loadedCargo; //cargos that assigned on truck
	Time MT; //Moving Time

	float& Speed;
	int& Capcity;

	int tDC; //total deliverid Cargos
	int tAT; //total active time


public:
	// constructor
	Truck(float& , int&);

	// Setters
	void SetMt(const Time& t); //company call it and send the time when the truck start moving

	// Getters 
	int GetDi() const; // calculate the delivery interval and send it to company
	const Time& GetMt() const; 
	float GetSpeed() const;
	int GetCapcity() const;
	const int getID() const { return ID; }

	CargoType getCargoType() const; // return NULL if empty
	PriorityQueue<Cargo*>  & getCargoList() ;

	//assign cargo to the Queue According to Distance
	virtual bool AssignCargo(Cargo* ) = 0;

	//check if there's cargo deleverid
	bool deliverCargo(Time* t);

};

