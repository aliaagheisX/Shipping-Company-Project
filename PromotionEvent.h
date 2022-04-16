#pragma once
#include "Event.h"
class PromotionEvent :public Event
{
    int ExtraMoney;
public:
    virtual void Execute(CargoList&);
    virtual void Read(ifstream& InputFile);
};

