#pragma once
#include "Truck.h"
class SpecialTruck : public Truck
{
    static float Speed;
    static int Capcity;
    static int CheckUPTime;
public:
    //constructor
    SpecialTruck();

    //assign cargo to the Queue According to Distance
    bool AssignCargo(Cargo* c);
    //Setters
    static void SetSpeed(const float& s);
    static void SetCapcity(const int& c);
    static void setCheckUPTime(const int& c);


};

