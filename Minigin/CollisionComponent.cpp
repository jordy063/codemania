#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "BoundingBoxComponent.h"

comps::CollisionComponent::CollisionComponent(std::list<std::shared_ptr<rectangle_>> collisionWalls, std::list<std::shared_ptr<rectangle_>> collisionPlatforms,
	std::shared_ptr<PhysicsComponent> physicsComp,std::shared_ptr<comps::BoundingBoxComponent> pBoundingBox)
	:m_CollisionWalls(collisionWalls)
	,m_CollisionPlatforms(collisionPlatforms)
	,m_pPhysicsComp(physicsComp)
	, m_pBoundingBoxComp(pBoundingBox)
{
}

void comps::CollisionComponent::SetExtraCollisions(std::list<std::shared_ptr<comps::BoundingBoxComponent>> extraCollisionList)
{
	m_ExtraCollisions.clear();

	auto currentBoundingBox = m_pBoundingBoxComp->GetBoundingBox(0, 0);
	for (std::shared_ptr<comps::BoundingBoxComponent> boundingBox : extraCollisionList)
	{
		rectangle_ boundingBoxRectangle = boundingBox->GetBoundingBox(0, 0);
		if (currentBoundingBox.posX != boundingBoxRectangle.posX && currentBoundingBox.posY != boundingBoxRectangle.posY)
		{
			m_ExtraCollisions.push_back(boundingBox);

		}
	}
}

void comps::CollisionComponent::SetCollision(std::list<std::shared_ptr<rectangle_>> collisionWalls, std::list<std::shared_ptr<rectangle_>> collisionPlatforms)
{
	m_CollisionWalls = collisionWalls;
	m_CollisionPlatforms = collisionPlatforms;
	m_pPhysicsComp->SetSpeedY(0);
}

void comps::CollisionComponent::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

void comps::CollisionComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::CollisionComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

	if (m_IsActive)
	{

		bool platFormTouchedY{ IsRectangleOverlapping(elapsedSecs * 2,false,m_CollisionPlatforms) };
		bool platFormTouchedYCurrent{ IsRectangleOverlapping(0, false,m_CollisionPlatforms) };
		bool wallsTouchedY{ IsRectangleOverlapping(elapsedSecs * 2, false, m_CollisionWalls) };


		if (platFormTouchedY && !platFormTouchedYCurrent)
		{
			if (m_pPhysicsComp->GetVelocity().y > 0)
			{
				m_pPhysicsComp->SetSpeedY(0);
				m_pPhysicsComp->SetAirborne(false);
			}
		}
		if (wallsTouchedY)
		{
			m_pPhysicsComp->SetSpeedY(0);
			m_pPhysicsComp->SetAirborne(false);
		}
		if (wallsTouchedY == false && platFormTouchedY == false)
		{
			m_pPhysicsComp->SetAirborne(true);
		}

		if (IsRectangleOverlapping(elapsedSecs * 2, true, m_CollisionWalls))
		{
			m_pPhysicsComp->SetSpeedX(0);
		}

		//also check for bullets. if they touch stop
		//shouldn't happen for normal bullets, only when they go up

		GetCollisionList();
		if (IsRectangleOverlapping(elapsedSecs * 2, true, m_CollisionList))
		{
			m_pPhysicsComp->SetSpeedX(0);
			m_pPhysicsComp->SetSpeedY(0);
		}
	}

}

bool comps::CollisionComponent::IsRectangleOverlapping(float elapsedSecs, bool xonly, std::list<std::shared_ptr<rectangle_>>& collision) const
{
	auto boundingBox{m_pBoundingBoxComp->GetBoundingBox(elapsedSecs,xonly) };

	float boundingboxLeft = boundingBox.posX;
	float boundingboxRight = boundingBox.posX + boundingBox.width;
	float boundingboxUp = boundingBox.posY;
	float boundingboxDown = boundingBox.posY + boundingBox.height;

	for (std::shared_ptr<rectangle_> collisionBox : collision)
	{
		float collisionboxLeft = collisionBox->posX;
		float collisionboxRight = collisionBox->posX + collisionBox->width;
		float collisionboxUp = collisionBox->posY;
		float collisionboxDown = collisionBox->posY + collisionBox->height;



		if (collisionboxLeft < boundingboxRight && boundingboxLeft < collisionboxRight && boundingboxUp < collisionboxDown && collisionboxUp < boundingboxDown)
			return true;

	}
	return false;

}

void comps::CollisionComponent::GetCollisionList()
{
	m_CollisionList.clear();
	for (std::shared_ptr<comps::BoundingBoxComponent> boundingBox : m_ExtraCollisions)
	{
		m_CollisionList.push_back(std::make_shared<rectangle_>(boundingBox->GetBoundingBox(0, 0)));
	}

	
}
