#include "MiniginPCH.h"
#include "InputObserver.h"


InputObserver::InputObserver(comps::InputComponent* inputComp)
	:pInputComp{ inputComp }
{
}

InputObserver::~InputObserver()
{
	delete pInputComp;
}


void InputObserver::Update(comps::Direction direction,float speed)
{
	pInputComp->changeDirection(direction,speed);
}
