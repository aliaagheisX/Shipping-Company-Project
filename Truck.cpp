#include "Truck.h"
int Truck::counter = 0;


Truck ::Truck(float& s, int& c): ID(counter + 1), Speed(s),Capcity(c)
{
	counter++;
}

int Truck::GetDi() const
{
	//! calculate Deleviery interval
	return DI;
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

int Truck::GetCapcity() const
{
	return Capcity;
}

string Truck::Print() const {
	return to_string(ID); // id truch []
}
