#include"CancellationEvent.h"
#include "Company.h"

void CancellationEvent::Execute(Company* cPtr) {
	Node<Cargo*>*temp= cPtr->getWaitingNormalCargo().getIterator(); // Get Itrator to find cargo with same ID
	
	while (temp && temp->getValue()->getID() != getId())
		temp = temp->getNext();
	
	//Check if found delete it
	if (temp){
		Cargo* t= temp->getValue();
		cPtr->getWaitingNormalCargo().removeValue(temp->getValue());
		delete t;
	}
}
void CancellationEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
}