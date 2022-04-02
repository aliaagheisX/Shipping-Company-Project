#pragma once
#include "Truck.h"
class NormalTruck :
    public Truck
{
    static float Speed;
    static long Capcity;
public:
    //constructor
    NormalTruck(long j);

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo* c);

};

