#include "MiniginPCH.h"
#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle(rectangle_* rectangle)
	:m_CollisionRect(rectangle)
{
}

std::shared_ptr<rectangle_> CollisionRectangle::GetRectangle() const
{
	return m_CollisionRect;
}
