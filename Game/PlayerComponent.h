#pragma once
#include "BaseComponent.h"
#include <shared_mutex>
namespace dae
{
	class Scene;
}
namespace comps
{
	class PhysicsComponent;
	class SpriteComponent;
	class InputComponent;
	class BoundingBoxComponent;
}
class PlayerComponent final :public comps::BaseComponent
{
public:
	PlayerComponent(int controllerId, int spriteId);
protected:
	virtual void Initialize(const dae::Scene& scene) override;
	virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;

	//may have to change to a health component
	void TakeDamage();


private:
	int m_ControllerId;
	int m_SpriteId;

	std::shared_ptr<comps::PhysicsComponent> m_pPhysicsComp;
	std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBoxComp;
	int m_Health;
	float2 screenDeathPosition;
	bool IsInvinsible;
};


//idea:
//in here we make the actual components and add them to the gameObject

