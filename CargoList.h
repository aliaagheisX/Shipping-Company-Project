#pragma once
#include"SpecialCargo.h"
#include"VIPCargo.h"
#include"NormalCargo.h"
#include"PiorityQueue.h"
#include"Queue.h"
#include"List.h"
class CargoList
{
	PiorityQueue<VIPCargo*> VIPCargos;
	Queue<SpecialCargo*> SpecialCargos;
	List<NormalCargo*> NormalCargos;

};

