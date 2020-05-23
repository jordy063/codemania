#include "MiniginPCH.h"
#include "InputObserver.h"


InputObserver::InputObserver(comps::InputComponent* inputComp,int controllerId)
	:pInputComp{ inputComp }
	,InputBaseObserver(controllerId)
{
}

InputObserver::~InputObserver()
{
	
}

void InputObserver::OnDirectionalKey(comps::Direction direction, bool move)
{
	if (move)
	{
		pInputComp->changeDirection(direction);
		if (direction == comps::Direction::LEFT || direction == comps::Direction::RIGHT)
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

void InputObserver::OnSelectKey(int spriteId)
{
	pInputComp->ShootBullet(m_CurrentDirection, spriteId);
}

