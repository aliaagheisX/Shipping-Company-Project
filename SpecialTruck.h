#pragma once
#include "Truck.h"
class SpecialTruck : public Truck
{
    static float Speed;
    static long Capcity;
public:
    //constructor
    SpecialTruck(long j);

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo* c);

};

