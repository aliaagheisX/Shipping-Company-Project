#pragma once
#include"Event.h"
class CancellationEvent : public Event {
public:
	virtual void Execute(Company* cPtr);
	virtual void Read(ifstream& InputFile);
};