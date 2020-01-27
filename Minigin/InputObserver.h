#pragma once
#include "Entity.h"

namespace comps
{
	class InputComponent;
}

class InputObserver
{

public:
	InputObserver(comps::InputComponent* inputComp);
	~InputObserver();

	void Update();
private:
	comps::InputComponent* pInputComp;
};
