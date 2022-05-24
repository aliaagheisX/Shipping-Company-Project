#pragma once
#include "Truck.h"
class VIPTruck : public Truck
{
    static int CheckUPTime;
public:
    //constructor
    VIPTruck(ifstream& InFile);
    static void setCheckUPTime(const int& c);
    virtual int GetCheckUPTime() const;
    virtual Types getTruckType()  const { return VIP; }

};

