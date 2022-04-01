#pragma once
#include "Cargo.h"
class VIPCargo :public Cargo
{
    double PT;
    double dist;
    double cost;
public:
    bool operator<(const VIPCargo& r) {
        return(PT + dist + cost     <    r.cost + r.dist + r.PT);
    }
};