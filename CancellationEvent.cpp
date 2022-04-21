#include"CancellationEvent.h"
#include "Company.h"

void CancellationEvent::Execute(Company* cPtr) {
	Node<Cargo*>*temp= cPtr->getWaitingNormalCargo().getIterator();
	
	while (temp && temp->getValue()->getID() != getId())
		temp = temp->getNext();
	
	if (temp){
		Cargo* t= temp->getValue();
		cPtr->getWaitingNormalCargo().removeValue(temp->getValue());
		delete t;
	}
}
void CancellationEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
}