#include "Cargo.h"
using namespace std;
#include<string>
//Cargo::Cargo(int i, char c) : ID(i), Types(c) {}


Cargo::Cargo(int i, char c, int Dst, int cst, int L,Time t) : ID(i), types(c)
{
	SetDeliveryDist(Dst);
	SetCost(cst);
	SetLt(L);
	Loadingtrcuk = NULL;
	PT = t;
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

void Cargo::setCDT(const Time& c) { 
	CDT = c; }

void Cargo::setLoadingTruck(const Truck* t)
{
	Loadingtrcuk = t;
}

void Cargo::setTypes(char c) {
	types = c;
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

int Cargo::GetDist() const
{
	return DeliveryDist;
}

int Cargo::GetCost() const
{
	return Cost;
}
int Cargo::getType() const
{
	if (types == 'N') return 0;
	if (types == 'V') return 2;
	return 1;
}
const Truck* Cargo::getLoadingTruck() const
{
	return Loadingtrcuk;
}
const int Cargo::getID() const
{
	return ID;
}
 bool Cargo::AutoPCheck(const Time& currentTime, int  AutoP)const
{
	return (currentTime.getDay() -PT.getDay() >= AutoP && currentTime.getHour() == PT.getHour());
}
const Time& Cargo::getCDT() const { return CDT; }


int Cargo::getPriority() const{ return -1*(0.5 * DeliveryDist + 0.3 * Cost + 2 * LT); }

 bool Cargo::MaxWCheck(const Time& currentTime, int MaxW)const
{
	 return ((currentTime - PT).ConvertToInt() >= MaxW && !Loadingtrcuk);
}

 void Cargo::output(ofstream& outfile) const
 {
	 outfile << CDT.TimePrint() << '\t' << ID << '\t' << PT.TimePrint() << '\t' << WT.TimePrint() << '\t' << Loadingtrcuk->getID() << '\n';
 }


