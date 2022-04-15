#include "Company.h"
#include<fstream>
#include<string>
using namespace std;
void Company::load()
{
	string path="Input_File.txt";
	ifstream file;
	file.open(path);
	file >> NormalTruckCount;
	file >> SpecialTruckCount;
	file >> VIPTruckCount;
	float speed;
	file>> speed;
	NormalTruck::SetSpeed(speed);

	file>> speed;
	SpecialTruck::SetSpeed(speed);

	file>> speed;
	VIPTruck::SetSpeed(speed);

	int capacity;
	file >> capacity;
	NormalTruck::SetCapcity(capacity);

	file >> capacity;
	SpecialTruck::SetCapcity(capacity);

	file >> capacity;
	VIPTruck::SetCapcity(capacity);

	int CheckUPTime;
	file >> CheckUPTime;
	NormalTruck::setCheckUPTime(CheckUPTime);

	file >> CheckUPTime;
	SpecialTruck::setCheckUPTime(CheckUPTime);

	file >> CheckUPTime;
	VIPTruck::setCheckUPTime(CheckUPTime);

	file >> J;

	file >> MaxW;
	file >> AutoP;

	int EventNumber;
	file >> EventNumber;
	for (int i = 0; i < EventNumber; i++)
	{
		char temp;
		file >> temp;
		if (temp == 'R')
		{
			char t;

		}
		else if (temp == 'X')
		{

		}
		else if(temp == 'P')
		{

		}
	}
}
