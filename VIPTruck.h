#pragma once
#include "Truck.h"
class VIPTruck :
    public Truck
{
    static Time MT;
    static float Speed;
    static long Capcity;
public:
    //constructor
    VIPTruck(long j);

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo*);

};

