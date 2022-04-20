#include "PreparationEvent.h"
#include"Cargo.h"
#include"Company.h"
void PreparationEvent::Execute(Company* cPtr) {
	Cargo* newCargo = new Cargo(getId());

	switch (CargoType)
	{
	case 'N':
		cPtr->getWaitingNormalCargo().addFront(newCargo);
		break; 
	
	case 'S':
		cPtr->getWaitingSpecialCargo().enqueue(newCargo);
		break;

	case 'V':
		cPtr->getWaitingVIPCargo().enqueue(newCargo, newCargo->getPriority());
		break;

	default:
		break;
	}

}

void PreparationEvent::Read(ifstream& InputFile) {
	InputFile >> CargoType;
	Event::Read(InputFile);
	InputFile >> Distances >> LoadTime >> Cost;
}