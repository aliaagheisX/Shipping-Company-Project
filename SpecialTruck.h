#pragma once
#include "Truck.h"
class SpecialTruck : public Truck
{
    static int CheckUPTime;
public:
    //constructor
    SpecialTruck(ifstream& InFile);
    static void setCheckUPTime(const int& c);
    virtual int GetCheckUPTime() const;
    virtual Types getTruckType()  const { return Special; }


};

