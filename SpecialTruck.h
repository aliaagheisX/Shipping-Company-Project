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

    static void SetSpeed(const float& s);
    static void SetCapcity(const int& c);
    static void setCheckUPTime(const int& c);
    virtual int GetCheckUPTime() const;


};

