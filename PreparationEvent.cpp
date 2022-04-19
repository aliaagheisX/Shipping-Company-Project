#include "PreparationEvent.h"

void PreparationEvent::Execute(Company* cPtr) {

}

void PreparationEvent::Read(ifstream& InputFile) {
	InputFile >> CargoType;
	Event::Read(InputFile);
	InputFile >> Distances >> LoadTime >> Cost;
}