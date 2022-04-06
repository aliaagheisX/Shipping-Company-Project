#include "Cargo.h"
Cargo::Cargo(int i) : ID(i) {}
void Cargo ::  SetPt(const Time& t)
{
	PT = t;
}
void Cargo ::  SetLt(const Time& t)
{
	LT = t;
}
void Cargo ::  SetWt(const Time& t)
{
	WT = t;
}
void Cargo :: SetDeliveryDist(const long& dist)
{
	if (dist < 0)
	{
		return;
	}
	DeliveryDist = dist;
}
void Cargo:: SetCost(const long& ct)
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
const Time& Cargo:: GetLt() const
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


