#pragma once
#include "Truck.h"
class NormalTruck : public Truck
{
    static float Speed;
    static int Capcity;
    static int CheckUPTime;
public:
    //constructor
    NormalTruck();

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo* c);

    static void SetSpeed(const float& s);
    static void SetCapcity(const int& c);
    static void setCheckUPTime(const int& c);


};

