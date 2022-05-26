#pragma once
#include "Time.h"
#include "PriorityQueue.h"
#include "Cargo.h"

enum Types {Normal, Special, VIP  };
class Truck
{
protected:
	static int counter;//counter for id
	int ID;

	Time DI; // delivery interval
	Time MT; //Moving Time

	Time FinishingLoadingTime;//For Not Overloading loading of Cargos on Truck
	Time FinishingCheckUPTime;//To End CheckUP

	PriorityQueue<Cargo*>* loadedCargo; //cargos that assigned or loaded on truck

	float Speed;
	int Capcity;

	bool NowMoving;//for not waiting in MaxWait
	bool isFailed;//for BONUS Failed Trucks
	bool isNightShift;//for Bonus : Night Shift

	int tDC; //total deliverid Cargos
	int tAT; //total active time
	int MaxCargoDist;//maximum distance will Truck Go

	int numberOfJourney;//number of journey Before CheckUP
						//return ZERO when check
	int totalJouneys;//number of actual journeies Done By Truck

	
	
	void Read(ifstream& InFile);//Read Function
								//use when we create new Truck
								//to read it's data from input file
public:
	// constructor
	//inialize all data
	//and call Read function to get Speed, Capacity, isNightShift
	Truck(ifstream& InFile);

	// Setters
	void setNowMoving(bool);//used in max wait
							//to inform truck that it loading and then Move 
							//whithout waiting another cargos
	void SetSpeed(const float s);//used in bonus
								 //when we need truck in maintaince


	// Getters 
	int GetCapcity() const;//Capacity of Truck
	float GetSpeed() const;//Capacity of Truck
	int getID() const;//ID
	int getPriority() const;
	bool getIsNightShift() const;
	const Time& getFinishingCheckUPTime() const;

	const Time& GetDi() const;//Delivery Interval
	const Time& GetMt() const; //Moving Time

	int getTotalActiveTime() const;//Total Active Time
	double getTruckUtilization(const Time&) const;//Calculate and Return Utilization of Truck 
												  //need Total simulation Time from Company

	const PriorityQueue<Cargo*>  * getCargoList() const; //retrun loaded|Assigned Cargos to Truck
	Types getCargoType() const;//return cargo type of loaded Cargos in Truck
	virtual Types getTruckType()  const = 0;//return Type of Truck 
											//overriden by [Normal|Special|VIP] Trucks
	
	virtual int GetCheckUPTime() const  = 0 ;//return checkup Time
											//overriden by [Normal|Special|VIP] Trucks


	//assign cargo to the Queue According to Distance
	bool AssignCargo(Cargo*,const Time &, bool = false); // handeling Night Shift AND loading Time
													     // if can assign add Cargo to loaded Cargo
														 // set Cargo's LoadedTruck to this Truck
														 // set Max Distance will Truck Cut till Now
	bool move(const Time*);	//Handeling Max wait | Loading Rule
							//set properties of journey in all cargos [WaitingTime, CargoDeliveryTime]
							// add cargos to loadedCargos By CargoDeliveryTime
							//set properties of journey in Truck [MovingTime, DeliveryInterval,MaxCargoDistance]
							//Update Statistics
	
	bool getIsFailed() const;	//[Bonus]if this truck failed or not
	void Failuer(const Time* t, UI* uiPtr);	//generate  a Probability
											//set properties of return back in all cargos [CargoDeliveryTime]
											// add cargos to loadedCargos By CargoDeliveryTime
											//set properties of journey in Truck [MovingTime, DeliveryInterval]
											//Print msg by failure
	
	Cargo* DeliverCargos(const Time &); //check CargoDeliveryTime of First Cargo in loaded cargos 
										//return this cargo  if it finish Delivery and unloading
									
	bool isFinishedDelivery(const Time& currentTime) const;// check if Truck returned back to home
	void EndJourney(); //reset all properties of journey && Update Statistice

	bool CheckUP(const Time& currentTime, int J, UI* uiptr);//generate  a Probability
															//Handel truck failure and regular of irregular checkups 
															//update properties of chekup of truck
															//print message
		
	bool isFinishedCheckUp(const Time& currentTime) const;
	void endCheckUp();//reset properties of checkups


	~Truck();
	//check if there's cargo deleverid


	
};

