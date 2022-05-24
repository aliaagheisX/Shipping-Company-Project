#pragma once
#include "Truck.h"
class NormalTruck : public Truck
{
    static int CheckUPTime;
public:
    NormalTruck(ifstream& InFile);
    static void setCheckUPTime(const int& c);
    virtual int GetCheckUPTime() const;
    virtual Types getTruckType()  const { return Normal; }


};

