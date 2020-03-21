
#pragma once
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include <iostream>

class SoundCommand
{

public:
	virtual ~SoundCommand() = default;
	virtual void Execute() = 0;
};


