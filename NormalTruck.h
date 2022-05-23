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

    static void SetSpeed(const float& s);
    static void SetCapcity(const int& c);
    static void setCheckUPTime(const int& c);
    virtual int GetCheckUPTime() const;
    virtual Types getTruckType()  const { return Normal; }


};

