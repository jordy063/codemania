#pragma once
#include "InputComponent.h"

class InputObserver
{

public:
	InputObserver(comps::InputComponent* inputComp,int controllerId);
	~InputObserver();

	void Update(comps::Direction direction, bool move);
	void ShootUpdate(int spriteId);
private:
	comps::InputComponent* pInputComp;
	comps::Direction m_CurrentDirection;
	int m_ControllerId;
};
