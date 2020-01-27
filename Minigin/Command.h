#pragma once
#include "Entity.h"

class Command
{
	
public:
	virtual ~Command() = default;
	virtual void Execute(const Entity* actor) = 0;
};
class MoveLeftCommand : public Command
{
public:
	void Execute(const Entity* actor) override {};

};
class MoveRightCommand : public Command
{
public:
	void Execute(const Entity* actor) override {};

};
class MoveUpCommand : public Command
{
public:
	void Execute(const Entity* actor) override {};

};
class MoveDownCommand : public Command
{
public:
	void Execute(const Entity* actor) override {};

};
