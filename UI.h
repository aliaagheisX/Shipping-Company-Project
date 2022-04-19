#pragma once
#include<string>
#include<iostream>

class Cargo;
class Truck;

using std::cout; using std::cin;using std::string;
enum Mode { Interactive, Silent, StepByStep};
class UI
{

	Mode mode;
	void ReadMode();

public:
	void Output(string s);
	void Line();

	void Print(Cargo* c);
	void Print(Truck* t);

};

