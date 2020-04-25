#include "MiniginPCH.h"
#include "BoundingBoxComponent.h"


comps::BoundingBoxComponent::BoundingBoxComponent(std::list < std::shared_ptr<rectangle_>> collisionWalls, std::list < std::shared_ptr<rectangle_>> collisionPlatforms, std::shared_ptr<PhysicsComponent> physicsComp, float width, float height)
	:m_CollisionWalls(collisionWalls)
	,m_CollisionPlatforms(collisionPlatforms)
	, m_pPhysicsComp(physicsComp)
	,m_Width(width)
	,m_Height(height)
{
}

rectangle_ comps::BoundingBoxComponent::GetBoundingBox(const float elapsedSecs, bool xonly) const
{
	float2 pos{};
	if (xonly){
		pos = m_pPhysicsComp->GetFuturePositionX(elapsedSecs);
	}
	else
	{
		pos = m_pPhysicsComp->GetFuturePositionY(elapsedSecs);
	}


	float xShift = (m_Width * (int)m_Alignment.first) / 2;
	float yShift = (m_Height * (int)m_Alignment.second) / 2;
	return rectangle_{ pos.x - xShift, pos.y - yShift, m_Width,m_Height };
}

void comps::BoundingBoxComponent::SetAlignment(HAlign hAlign, VAlign vAlign)
{
	m_Alignment.first = hAlign;
	m_Alignment.second = vAlign;
}

void comps::BoundingBoxComponent::SetNewBoundingBox(std::list<std::shared_ptr<rectangle_>> collisionWalls, std::list<std::shared_ptr<rectangle_>> collisionPlatforms)
{
	m_CollisionWalls = collisionWalls;
	m_CollisionPlatforms = collisionPlatforms;
}

void comps::BoundingBoxComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
}

void comps::BoundingBoxComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);
	

	//if (IsRectangleOverlapping(elapsedSecs * 2, false, m_CollisionWalls) && !IsRectangleOverlapping(0, false, m_CollisionWalls))
	//{
	//	if (m_pPhysicsComp->GetVelocity().y > 0)
	//	{
	//		m_pPhysicsComp->SetSpeedY(0);
	//		m_pPhysicsComp->SetAirborne(false);
	//	}
	//}
	//else
	//{
	//	m_pPhysicsComp->SetAirborne(true);
	//}
	//if (IsRectangleOverlapping(elapsedSecs * 2, true, m_CollisionWalls))
	//{
	//	m_pPhysicsComp->SetSpeedX(0);
	//}

	//if (IsRectangleOverlapping(elapsedSecs * 2, false, m_CollisionPlatforms) && !IsRectangleOverlapping(0, false, m_CollisionPlatforms))
	//{
	//	if (m_pPhysicsComp->GetVelocity().y > 0)
	//	{
	//		m_pPhysicsComp->SetSpeedY(0);
	//		m_pPhysicsComp->SetAirborne(false);
	//	}
	//}
	//else
	//{
	//	m_pPhysicsComp->SetAirborne(true);
	//}
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



}
bool comps::BoundingBoxComponent::IsRectangleOverlapping(float elapsedSecs,bool xonly, std::list < std::shared_ptr<rectangle_>>& collision)
{
	auto boundingBox{ GetBoundingBox(elapsedSecs,xonly) };

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



		if (collisionboxLeft < boundingboxRight && boundingboxLeft < collisionboxRight && boundingboxUp < collisionboxDown&& collisionboxUp < boundingboxDown)
			return true;

	}
	return false;

}

