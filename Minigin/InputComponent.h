#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"





class InputComponent : comps::BaseComponent
{
public:

	InputComponent(comps::PhysicsComponent physicsComp, comps::SpriteComponent spriteComp);
	~InputComponent();



private:

};

