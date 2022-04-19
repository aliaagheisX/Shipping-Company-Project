#include"CancellationEvent.h"
#include "Company.h"
void CancellationEvent::Execute(Company* cPtr) {
	Node<NormalCargo*>*temp=cPtr->getWaitingNormalCargo().getIterator();
	while (temp)
	{
		if (temp->getValue()->getID() == getId())
		{
			break;
		}
		temp = temp->getNext();
	}
	if (temp)
	{
		cPtr->getWaitingNormalCargo().removeValue(temp->getValue());
	}
	return;


}
void CancellationEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
}