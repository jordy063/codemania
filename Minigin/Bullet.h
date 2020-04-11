#pragma once
#include "Entity.h"
#include "PhysicsComponent.h"
class Bullet : public Entity
{
public:
	Bullet(comps::Direction direction,float speed, std::shared_ptr<dae::Scene> scene);
	void CreateComponents() override;

private:
	comps::Direction m_Direction;
	float m_Speed;
};

