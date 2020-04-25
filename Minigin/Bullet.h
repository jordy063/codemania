#pragma once
#include "Entity.h"
#include "PhysicsComponent.h"
class Bullet : public Entity
{
public:
	Bullet(comps::Direction direction,float speed, std::shared_ptr<dae::Scene> scene,int id);
	void CreateComponents(int id);

private:
	comps::Direction m_Direction;
	float m_Speed;
	int m_PlayerId;
};

