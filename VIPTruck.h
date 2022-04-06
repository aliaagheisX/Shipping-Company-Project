#pragma once
#include "Truck.h"
class VIPTruck :
    public Truck
{
    static int CheckUPTime;
    static float Speed;
    static long Capcity;
public:
    //constructor
    VIPTruck(long j);

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo*);

    static void SetSpeed(const float& s);
    static void SetCapcity(const long& c);
    static void setCheckUPTime(const int& c);

};

