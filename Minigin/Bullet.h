#pragma once
#include "Entity.h"
#include "PhysicsComponent.h"
class Bullet : public Entity
{
public:
	Bullet(comps::Direction direction,float speed);
	void CreateComponents() override;

private:
	comps::Direction m_Direction;
	float m_Speed;
};

