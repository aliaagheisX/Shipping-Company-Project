#pragma once
#include "Truck.h"
class VIPTruck : public Truck
{
    
    static float Speed;
    static int Capcity;
    static int CheckUPTime;
public:
    //constructor
    VIPTruck();

    static void SetSpeed(const float& s);
    static void SetCapcity(const int& c);
    static void setCheckUPTime(const int& c);

};

