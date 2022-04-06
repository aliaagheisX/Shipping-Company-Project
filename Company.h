#pragma once
#include<iostream>

class VIPCargo;
class NormalCargo;
class SpecialCargo;
class Cargo;
class VIPTruck;

class Company
{
	void fun() {
		int vip, special, cargo;
		std::cin >> vip >> special >> cargo;
		VIPTruck::Speed = vip;
	}
};

