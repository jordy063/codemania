#include "MiniginPCH.h"
#include "BoundingBoxComponent.h"


comps::BoundingBoxComponent::BoundingBoxComponent(float width, float height,std::shared_ptr<comps::PhysicsComponent> pPhysicsComp)
	:m_Width(width)
	,m_Height(height)
	,m_pPhysicsComp(pPhysicsComp)

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

bool comps::BoundingBoxComponent::IsOverlapping(std::shared_ptr<BoundingBoxComponent> pBoundingBox)
{
	rectangle_ BoundingBox1 = pBoundingBox->GetBoundingBox(0,false);
	rectangle_ BoundingBox2 = GetBoundingBox(0, false);

	auto BoundingBox1Left = BoundingBox1.posX;
	auto BoundingBox1Right = BoundingBox1.posX + BoundingBox1.width;
	auto BoundingBox1Top = BoundingBox1.posY;
	auto BoundingBox1Bottom = BoundingBox1.posY + BoundingBox1.height;

	auto BoundingBox2Left = BoundingBox2.posX;
	auto BoundingBox2Right = BoundingBox2.posX + BoundingBox2.width;
	auto BoundingBox2Top = BoundingBox2.posY;
	auto BoundingBox2Bottom = BoundingBox2.posY + BoundingBox2.height;

	if (BoundingBox2Left < BoundingBox1Right && BoundingBox1Left < BoundingBox2Right && BoundingBox1Top < BoundingBox2Bottom && BoundingBox2Top < BoundingBox1Bottom)
	{
		return true;
	}
	return false;
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

}

