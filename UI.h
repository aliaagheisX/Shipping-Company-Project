#pragma once
#include<string>
#include<iostream>
using std::cout; using std::cin;using std::string;

class Cargo;
class Truck;
class Company;

enum Mode { Interactive, StepByStep, Silent};
class UI
{

	Mode mode;
	void PrintScreen(Company*);
	void InterActiveMode(Company*);
	void StepByStepMode(Company*);

public:
	UI();
	void Line();
	void Output(string s);
	void Print(Cargo* c, char seperator = ',');
	void Print(Truck* t, char seprator = ' ');
	void Print(int n, char seperator = ',');

	void Print(Company*);
	~UI();
};

