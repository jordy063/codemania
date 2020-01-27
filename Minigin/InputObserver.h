#pragma once
#include "Entity.h"
#include "InputComponent.h"

class InputObserver
{

public:
	InputObserver(comps::InputComponent* inputComp);
	~InputObserver();

	void Update(comps::Direction direction, float speed);
private:
	comps::InputComponent* pInputComp;
};
