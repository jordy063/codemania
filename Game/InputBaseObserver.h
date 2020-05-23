#pragma once
#include "InputComponent.h"

class InputBaseObserver
{
public:
	InputBaseObserver(int controllerId);

	virtual void OnDirectionalKey(comps::Direction direction, bool move) = 0;
	virtual void OnSelectKey(int spriteId) = 0;
protected:

	int m_ControllerId;
};

