#include "MiniginPCH.h"
#include "InputObserver.h"


InputObserver::InputObserver(comps::InputComponent* inputComp)
	:pInputComp{ inputComp }
{
}

InputObserver::~InputObserver()
{
	
}


void InputObserver::Update(comps::Direction direction,bool move)
{
	if (move)
	{
		pInputComp->changeDirection(direction);
		m_CurrentDirection = direction;
	}


	else
	{
		if (direction == m_CurrentDirection)
		{
			pInputComp->StopMoving();
		}

	}
		
}
