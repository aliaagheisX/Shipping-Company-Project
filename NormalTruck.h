#pragma once
#include "Truck.h"
class NormalTruck :
    public Truck
{
    static float Speed;
    static long Capcity;
    static int CheckUPTime;
public:
    //constructor
    NormalTruck(long j);

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo* c);

    static void SetSpeed(const float& s);
    static void SetCapcity(const long& c);
    static void setCheckUPTime(const int& c);


};

