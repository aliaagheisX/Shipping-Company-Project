#include "Time.h"
#include"UI.h"
//get Day then Hour From Constructor
Time::Time(int d, int h) {
	setDay(d);
	setHour(h);
}


//setters
void Time::setHour(int h) {
	while (h > 24)
	{
		h -= 24;
		day++;
	}
	hour = h;
}

void Time::setDay(int d) {
	day = d;
}

//getters
int Time::getHour() const { return hour; }
int Time::getDay() const { return day; }

//operators
bool Time::operator<(const Time& t) {

	if (day == t.day) //if the same compare the hour
		return (hour < t.hour);

	else return (day < t.day); // else compare day
}

bool Time::operator==(const Time& t) {

	return (day == t.day && hour == t.hour);
}

// increase hour by 1 and 
//if pass 24 hr increase the day 1
void Time::Update(){ 

	setHour(hour + 1); // in set Hour it handel if it enter new day

}

void Time::Read(ifstream& InFile) {
	char buff;
	InFile >> day >> buff >> hour;
}

void Time::Out(ofstream& OutFile) const
{
	OutFile << to_string(day) + ":" + to_string(hour);
}

void Time::Print(UI* uiPtr) const {
	uiPtr->Output(to_string(day) + ":" + to_string(hour));
}