#pragma once
#include "Time.h"
#include "PriorityQueue.h"
#include "Cargo.h"
enum Types {Normal, Special, VIP  };
class Truck
{
protected:
	static int counter;
	int ID;
	
	Time DI; // delivery interval
	PriorityQueue<Cargo*> loadedCargo; //cargos that assigned on truck
	Time MT; //Moving Time
	Time FinishingLoadingTime;

	float& Speed;
	int& Capcity;

	int tDC; //total deliverid Cargos
	int tAT; //total active time
	int j;

public:
	// constructor
	Truck(float& , int&);

	// Setters
	void SetMt(const Time& t); //company call it and send the time when the truck start moving

	void Setj (int x);


	// Getters 
	Time GetDi() const; // calculate the delivery interval and send it to company
	const Time& GetMt() const; 
	float GetSpeed() const;
	int GetCapcity() const;
	const int getID() const { return ID; }

	int Getj() const;
	Time GetFLT() const;
	bool move(const Time* t , bool now = false);

  
	Types getTypes() const; // return NULL if empty
	PriorityQueue<Cargo*>  & getCargoList() ;

	//assign cargo to the Queue According to Distance
	bool AssignCargo(Cargo*,const Time &);

	//check if there's cargo deleverid
	bool deliverCargo(Time* t);

};

