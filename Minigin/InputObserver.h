#pragma once
#include "Entity.h"

class Observer
{

public:
	virtual ~Observer() = default;
	virtual void Execute(const Entity* actor) = 0;
};
class MoveLeftCommand : public Observer
{
public:
	void Execute(const Entity* actor) override {};

};
class MoveRightCommand : public Observer
{
public:
	void Execute(const Entity* actor) override {};

};
class MoveUpCommand : public Observer
{
public:
	void Execute(const Entity* actor) override {};

};
class MoveDownCommand : public Observer
{
public:
	void Execute(const Entity* actor) override {};

};