#pragma once
#include"List.h"
#include "Truck.h"
class TruckList
{
	List<Truck*> VIPTrucks; // Truck.print() => CargoList.print() => {VipCargos.print()} (Normal.print())
	List<Truck*> NormalTrucks;
	List<Truck*> SpecialTrucks;


};

