#pragma once
#include "InputComponent.h"

class InputObserver
{

public:
	InputObserver(comps::InputComponent* inputComp);
	~InputObserver();

	void Update(comps::Direction direction, bool move);
	void ShootUpdate();
private:
	comps::InputComponent* pInputComp;
	comps::Direction m_CurrentDirection;
};
