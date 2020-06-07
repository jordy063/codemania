#include "MiniginPCH.h"
#include "ScorePopUpManager.h"
#include "ScorePopUpComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "TransformComponent.h"

void ScorePopUpManager::MakeScorePopUp(ItemType itemType,int spriteId,float2 position)
{
	//make a gameobject with a certain component
	//we need to set a specific for a spritecomp. not a texturecomp
	
	auto pScoreObject = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	pScoreObject->GetTransform()->Translate(position);
	dae::SceneManager::GetInstance().GetActiveScene()->Add(pScoreObject);
	std::shared_ptr <comps::SpriteComponent> spriteComp = std::shared_ptr <comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/scores.png", 1, 6,spriteId,0.2f,16,16 ));;
	
	spriteComp->SetBeginEndFrames(itemType * 2 + spriteId, itemType * 2 + spriteId);

	auto physicsComp = std::shared_ptr <comps::PhysicsComponent>(new comps::PhysicsComponent(pScoreObject->GetTransform(),false,0));
	physicsComp->SetSpeedY(-20);

	auto scorePopUpComp = std::shared_ptr <comps::ScorePopUpComponent>(new comps::ScorePopUpComponent(physicsComp,itemType));

	pScoreObject->AddComponent(spriteComp, ComponentType::SPRITECOMP);
	pScoreObject->AddComponent(physicsComp, ComponentType::PHYSICSCOMP);
	pScoreObject->AddComponent(scorePopUpComp, ComponentType::SCOREPOPUPCOMPONENT);

	m_pScoreObjects.insert(pScoreObject);
}

void ScorePopUpManager::RemoveScorePopUp(std::shared_ptr <TransformComponent> pTransform)
{
	std::shared_ptr <dae::GameObject> pGameObjectToRemove{ nullptr };
	for (std::shared_ptr <dae::GameObject> pScoreObject : m_pScoreObjects)
	{
		if (pScoreObject->GetTransform()->GetPosition().x == pTransform->GetPosition().x &&
			pScoreObject->GetTransform()->GetPosition().y == pTransform->GetPosition().y)
		{
			pScoreObject->Clear();
			pGameObjectToRemove = pScoreObject;
		}
	}
	if (pGameObjectToRemove == nullptr)
	{
		m_pScoreObjects.erase(pGameObjectToRemove);
	}

}
