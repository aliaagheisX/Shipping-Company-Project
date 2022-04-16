#pragma once
#include<fstream>
using namespace std;
class Time
{
	int hour;
	int day;
public:

	Time(int = 1, int = 1);
	//setters
	void setHour(int);
	void setDay(int);

	//getters
	int getHour() const;
	int getDay() const;

	//operators
	bool operator<(const Time&);
	bool operator==(const Time&);

	//updates
	void Update(); // increase hour by 1 and 
				   //if pass 24 hr increase the day 1
	void Read(ifstream& InFile);


};


