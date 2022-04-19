#pragma once
#include "Event.h"
#include "List.h"

#include "PriorityQueue.h"
class PromotionEvent :public Event
{
    int ExtraMoney;
public:
    virtual void Execute(Company* cPtr);
    virtual void Read(ifstream& InputFile);
};

