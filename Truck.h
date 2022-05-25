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
	PriorityQueue<Cargo*>* loadedCargo; //cargos that assigned on truck
	Time MT; //Moving Time
	Time FinishingLoadingTime;//For Not Overloading loading of Cargos on Truck
	Time FinishingCheckUPTime;//To End CheckUP
	float Speed;
	int Capcity;
	int tDC; //total deliverid Cargos
	int tAT; //total active time
	int MaxCargoDist;//maximum distance will Truck Go

	int numberOfJourney;//number of journey Before CheckUP
						//return ZERO when check
	int totalJouneys;//number of actual journeies Done By Truck

	bool isFailed;
	bool NowMoving;//for not waiting in MaxWait
	bool aPartMantainance;
public:
	// constructor
	Truck(ifstream& InFile);

	// Setters
	void SetMt(const Time& t); //company call it and send the time when the truck start moving
	void SetNumberOfJourney(int x);
	void setNowMoving(bool);




	// Getters 
	Time GetDi() const; // calculate the delivery interval and send it to company
	const Time& GetMt() const; 
	float GetSpeed() const;
	int GetCapcity() const;
	const int getID() const { return ID; }
	virtual int GetCheckUPTime() const  = 0 ;
	int getNumberOfJourney() const;
	PriorityQueue<Cargo*>  * getCargoList() ;
	bool getNowMoving() const { return NowMoving; }
	int getTotalActiveTime() const;
	double getTruckUtilization(const Time&);
	Types getTypes() const;
	bool getIsFailed() const { return isFailed; }

	virtual Types getTruckType()  const = 0;


	//assign cargo to the Queue According to Distance
	bool AssignCargo(Cargo*,const Time &);
	bool move(const Time* t);
	void EndJourney();
	Cargo* DeliverCargos(const Time &);
	void Failuer(const Time* t, UI* uiPtr);
	bool isApart();


	bool CheckUP(const Time& currentTime, int J);
	bool isFinishedCheckUp(const Time& currentTime) const;
	void endCheckUp();


	void SetSpeed(const float s);
	void SetCapcity(const int c);

	////
	void Read(ifstream& InFile);
	////
	int getPriority() const { return -1 * (0.5*Speed + 8*Capcity); }
	bool isFinishedDelivery(const Time& currentTime) const;
	~Truck();
	//check if there's cargo deleverid


	
};

