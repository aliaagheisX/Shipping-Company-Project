#include "PreparationEvent.h"
#include"Cargo.h"
#include"Company.h"
void PreparationEvent::Execute(Company* cPtr) {
	Cargo* newCargo = new Cargo(getId(), Types,Distances,Cost,LoadTime, EventTime);
	switch (Types)
	{
	case 'N':
		cPtr->getWaitingNormalCargo().addBack(newCargo);
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
	InputFile >> Types;
	Event::Read(InputFile);
	InputFile >> Distances >> LoadTime >> Cost;
}