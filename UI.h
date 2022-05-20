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
	void ReadMode();
	void Line();
	void Output(string s);
	void Print(Cargo* c);
	void Print(Truck* t);
	void Print(int n);

	void Print(Company*);

};

