#include "MiniginPCH.h"
#include "InputObserver.h"
#include "InputComponent.h"

void InputObserver::Update()
{
	pInputComp->changeDirection(comps::Direction::DOWN);
}
