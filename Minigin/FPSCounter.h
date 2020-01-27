#pragma once
#include "Entity.h"
class FPSCounter : public Entity
{
public:
	FPSCounter();
	void CreateComponents() override;
};
