#pragma once
#include "Cargo.h"
class VIPCargo :public Cargo
{
	//int PriorityEquation = GetCost() + 0.8*GetDist();
public:
	VIPCargo(int i);
	int getPriority();
};