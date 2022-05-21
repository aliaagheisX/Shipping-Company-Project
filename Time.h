#pragma once
#include<fstream>

class UI;
using namespace std;
class Time
{
	int hour;
	int day;
public:

	Time(int = 0, int = 0);
	//setters
	void setHour(int);
	void setDay(int);

	//getters
	int getHour() const;
	int getDay() const;

	//operators
	bool operator<(const Time&) const;
	bool operator==(const Time&) const;
	bool operator<=(const Time&) const;
	Time operator+(const Time&) const;
	Time operator+(const int) const;
	int operator-(const Time&) const;

	//updates
	void Update(); // increase hour by 1 and 
				   //if pass 24 hr increase the day 1

	void Read(ifstream& InFile);
	string TimePrint() const;

	//Extras
	int ConvertToInt() const;


};


