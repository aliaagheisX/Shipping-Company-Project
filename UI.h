#pragma once
#include<string>
#include<iostream>
using std::cout; using std::cin;using std::string;

class Cargo;
class Truck;
class Company;

//char open[3] = { '[', '(', '{' };
//char close[3] = { ']', ')', '}' };
enum Mode { Interactive, Silent, StepByStep};
class UI
{

	Mode mode;
	void ReadMode();

public:
	void Output(string s);
	void Line();

	void PrintData(Company*);
	void Print(Cargo* c);
	void Print(Truck* t);



};

