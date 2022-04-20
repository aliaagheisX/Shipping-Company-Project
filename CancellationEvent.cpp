#include"CancellationEvent.h"
#include "Company.h"

void CancellationEvent::Execute(Company* cPtr) {
	Node<Cargo*>*temp= cPtr->getWaitingNormalCargo().getIterator();
	
	while (temp && temp->getValue()->getID() != getId())
		temp = temp->getNext();
	
	if (temp)
		cPtr->getWaitingNormalCargo().removeValue(temp->getValue());
}
void CancellationEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
}