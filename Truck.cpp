#include "Truck.h"
Truck ::Truck(float& s, long& c): Speed(s),Capcity(c)
{
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

void Truck::SetSpeed(const float& s)
{
	Speed = s;
}

void Truck::SetCapcity(const long& c)
{
	Capcity = c;
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