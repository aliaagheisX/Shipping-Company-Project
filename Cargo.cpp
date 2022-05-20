#include "Cargo.h"
using namespace std;
#include<string>
Cargo::Cargo(int i, char c) : ID(i), cargoType(c) {}


Cargo::Cargo(int i, char c, int Dst, int cst, int L,Time t) : ID(i), cargoType(c)
{
	SetDeliveryDist(Dst);
	SetCost(cst);
	SetLt(L);
	Loadingtrcuk = NULL;
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
void Cargo::SetStart(const Time& t)
{
	Start = t;
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

void Cargo::setCDT(Time& c) { CDT = c; }

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

const Time& Cargo::GetStart() const
{
	return Start;
}

int Cargo::GetDist() const
{
	return DeliveryDist;
}

int Cargo::GetCost() const
{
	return Cost;
}
const int Cargo::getID() const
{
	return ID;
}


int Cargo::getPriority() const{ return 0.5 * DeliveryDist + 0.3 * Cost + 2 * LT; }
