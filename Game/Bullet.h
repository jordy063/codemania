#pragma once
#include "Entity.h"
#include "PhysicsComponent.h"

namespace dae
{
	class Scene;
}
class Bullet : public Entity
{
public:
	Bullet(comps::Direction direction,float speed, std::shared_ptr<dae::Scene> scene,int id);
	void CreateComponents(int id, std::shared_ptr<dae::Scene> scene);
private:
	comps::Direction m_Direction;
	float m_Speed;
	int m_PlayerId;
};

