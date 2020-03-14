#pragma once
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include <iostream>

class Command
{
	
public:
	virtual ~Command() = default;
	virtual void Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed) = 0;
};
class MoveLeftCommand : public Command
{
public:
	void Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp,std::shared_ptr<comps::SpriteComponent> spriteComp, float speed) override;

};
class MoveRightCommand : public Command
{
public:
	void Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed) override;

};
class MoveUpCommand : public Command
{
public:
	void Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed) override;

};
class MoveDownCommand : public Command
{
public:
	void Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed) override;

};
class StopMovingCommand : public Command
{
public:
	void Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed) override;

};
