#include "PreparationEvent.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VIPCargo.h"
#include"Company.h"
void PreparationEvent::Execute(Company* cPtr) {
	
	switch (CargoType)
	{
	case 'N':
	{NormalCargo* normalCargo = new NormalCargo(getId());
	cPtr->getWaitingNormalCargo().addFront(normalCargo);
	break; 
	}
	case 'S':
	{SpecialCargo* spectialCargo = new SpecialCargo(getId());
	cPtr->getWaitingSpecialCargo().enqueue(spectialCargo);
	}
	case 'V':
	{
		VIPCargo* VipCargo = new VIPCargo(getId());
		cPtr->getWaitingVIPCargo().enqueue(VipCargo, VipCargo->getPriority());
	}
	default:
		break;
	}

}

void PreparationEvent::Read(ifstream& InputFile) {
	InputFile >> CargoType;
	Event::Read(InputFile);
	InputFile >> Distances >> LoadTime >> Cost;
}