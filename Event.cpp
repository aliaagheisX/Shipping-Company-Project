#include "Event.h"
void Event::Read(ifstream& InputFile) {
	EventTime.Read(InputFile);
	InputFile >> CargoID;
}

int Event::getId() const
{
	return CargoID;
}
