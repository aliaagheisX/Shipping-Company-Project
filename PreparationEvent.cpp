#include "PreparationEvent.h"

void PreparationEvent::Execute(CargoList& c) {

}

void PreparationEvent::Read(ifstream& InputFile) {
	InputFile >> CargoType;
	Event::Read(InputFile);
	InputFile >> Distances >> LoadTime >> Cost;
}