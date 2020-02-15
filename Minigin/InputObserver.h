#pragma once
#include "Entity.h"
#include "InputComponent.h"

class InputObserver
{

public:
	InputObserver(comps::InputComponent* inputComp);
	~InputObserver();

	void Update(comps::Direction direction, bool move);
private:
	comps::InputComponent* pInputComp;
	comps::Direction m_CurrentDirection;
};
