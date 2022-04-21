#include"PromotionEvent.h"
#include "Company.h"

void PromotionEvent::Execute(Company* cPtr) {
	Node<Cargo*>* temp = cPtr->getWaitingNormalCargo().getIterator();
	while (temp && temp->getValue()->getID() != getId())
		temp = temp->getNext();
	if (temp)
	{
		temp->getValue()->setCargoType('V');
		temp->getValue()->SetCost(temp->getValue()->GetCost() + ExtraMoney);
		cPtr->getWaitingNormalCargo().removeValue(temp->getValue());
		cPtr->getWaitingVIPCargo().enqueue(temp->getValue(), temp->getValue()->getPriority());
	}
}


void PromotionEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
	InputFile >> ExtraMoney;
}