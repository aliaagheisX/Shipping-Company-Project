#include"PromotionEvent.h"

void PromotionEvent::Execute(Company* cPtr) {

}


void PromotionEvent::Read(ifstream& InputFile) {
	Event::Read(InputFile);
	InputFile >> ExtraMoney;
}