#include "Cargo.h"
using namespace std;
#include<string>
Cargo::Cargo(int i, char c) : ID(i), cargoType(c) {}


Cargo::Cargo(int i, char c, double Dst, double cst, int L) :Cargo(i,c)
{
	SetDeliveryDist(Dst);
	SetCost(cst);
	SetLt(L);
}

void Cargo ::  SetPt(const Time& t)
{
	PT = t;
}
void Cargo ::  SetLt(const int& t)
{
	LT = t;
}
void Cargo ::  SetWt(const Time& t)
{
	WT = t;
}
void Cargo :: SetDeliveryDist(const int& dist)
{
	if (dist < 0)
	{
		return;
	}
	DeliveryDist = dist;
}
void Cargo:: SetCost(const int& ct)
{
	if (ct < 0)
	{
		return;
	}
	Cost = ct;
}

const Time& Cargo:: GetPt() const
{
	return PT;
}
const int Cargo:: GetLt() const
{
	return LT;
}
const Time& Cargo:: GetWt() const
{
	return WT;
}

double Cargo::GetDist() const
{
	return DeliveryDist;
}

double Cargo::GetCost() const
{
	return Cost;
}
const int Cargo::getID() const
{
	return ID;
}


