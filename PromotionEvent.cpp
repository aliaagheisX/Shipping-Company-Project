#include"PromotionEvent.h"

void PromotionEvent::Execute(CargoList& c) {

}


void PromotionEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
	InputFile >> ExtraMoney;
}