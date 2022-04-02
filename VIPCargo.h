#pragma once
#include "Cargo.h"
class VIPCargo :public Cargo
{
    int PiorityEquation;
public:
    bool operator<(const VIPCargo& r) {
      // Waiting for the Priority Equation
    }
};