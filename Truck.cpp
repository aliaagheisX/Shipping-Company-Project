#include "Truck.h"
int Truck::counter = 0;


Truck ::Truck(float& s, long& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
}

void Truck::SetJ(const long& j)
{
	J = j;
}

int Truck::GetDi() const
{
	//! calculate Deleviery interval
	return DI;
}

long Truck::GetJ() const
{
	return J;
}


void Truck::SetMt(const Time& t)
{
	MT = t;
}

const Time& Truck::GetMt() const
{
	return MT;
}

float Truck::GetSpeed() const
{
	return Speed;
}

long Truck::GetCapcity() const
{
	return Capcity;
}