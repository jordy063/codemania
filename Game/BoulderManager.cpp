#include "MiniginPCH.h"
#include "BoulderManager.h"
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include "SpriteComponent.h"
#include "BoulderComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "TileMapLoader.h"
#include "GameObject.h"
#include "HealthComponent.h"


void BoulderManager::MakeBoulder(std::shared_ptr<TransformComponent> transform,comps::Direction direction)
{
	auto pBoulderObject{ std::shared_ptr<dae::GameObject>(new dae::GameObject()) };
	dae::SceneManager::GetInstance().GetActiveScene()->Add(pBoulderObject);

	auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/boulders.png", 2, 4, 0, 0.2f, 32, 16));
	
	auto pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(pBoulderObject->GetTransform(), true, 30.0f));

	auto pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(16, 16, pPhysicsComp));
	auto pCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		dae::SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), pPhysicsComp, pBoundingBox));
	auto pBoulderBox = std::shared_ptr<comps::BoulderComponent>(new comps::BoulderComponent(pPhysicsComp, pBoundingBox, m_PlayerHealthComps));

	
	pBoulderObject->AddComponent(pSpriteComp, ComponentType::SPRITECOMP);
	pBoulderObject->AddComponent(pBoundingBox, ComponentType::BOUNDINGBOXCOMP);
	pBoulderObject->AddComponent(pCollisionComp, ComponentType::COLLISIONCOMPONENT);
	pBoulderObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	pBoulderObject->AddComponent(pBoulderBox, ComponentType::BOULDERCOMPONENT);

	pBoulderObject->GetTransform()->Translate(transform->GetPosition());

	
	if (direction == comps::Direction::RIGHT)
	{
		pSpriteComp->SetBeginEndFrames(0, 3);
		pPhysicsComp->SetSpeedX(m_BoulderSpeed);
	}
	else if(direction == comps::Direction::LEFT)
	{
		pSpriteComp->SetBeginEndFrames(4, 7);
		pPhysicsComp->SetSpeedX(-m_BoulderSpeed);
	}

	m_pBoulders.insert(pBoulderObject);
}

void BoulderManager::RemoveBoulder(std::shared_ptr <TransformComponent> pTransform)
{
	std::shared_ptr <dae::GameObject> pGameObjectToRemove{ nullptr };
	for (std::shared_ptr <dae::GameObject> pBoulderObject : m_pBoulders)
	{
		if (pBoulderObject->GetTransform()->GetPosition().x == pTransform->GetPosition().x &&
			pBoulderObject->GetTransform()->GetPosition().y == pTransform->GetPosition().y)
		{
			pBoulderObject->Disable();
			pGameObjectToRemove = pBoulderObject;
		}
	}
	if (pGameObjectToRemove == nullptr)
	{
		m_pBoulders.erase(pGameObjectToRemove);
	}
}

bool BoulderManager::CheckIfHit(std::shared_ptr<comps::BoundingBoxComponent> pBoulderBoundingBox, int playerId)
{
	//checks if player and current bullet overlap

	bool isHit{ m_pPlayerBoundingBoxes[playerId]->IsOverlapping(pBoulderBoundingBox) };
	if (isHit)
	{
		return true;
	}

	return false;
	//
	//return m_pPlayerBoundingBox->IsOverlapping(pBulletBoundingBox);

}

void BoulderManager::RegisterPlayers(const std::vector<std::shared_ptr<dae::GameObject>>& pPlayers)
{
	for (std::shared_ptr<dae::GameObject> pPlayerObject : pPlayers)
	{
		auto boundingBoxComp = pPlayerObject->GetComponent(ComponentType::BOUNDINGBOXCOMP);
		m_pPlayerBoundingBoxes.push_back(std::dynamic_pointer_cast<comps::BoundingBoxComponent>(boundingBoxComp));

		auto playerHealthComp = pPlayerObject->GetComponent(ComponentType::HEALTHCOMPONENT);
		m_PlayerHealthComps.push_back(std::dynamic_pointer_cast<comps::HealthComponent>(playerHealthComp));
		
	}
}
