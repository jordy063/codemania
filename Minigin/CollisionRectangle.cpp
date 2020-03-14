#include "MiniginPCH.h"
#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle(std::shared_ptr< Rectangle_> rectangle)
	:m_CollisionRect(rectangle)
{
}

std::shared_ptr<Rectangle_> CollisionRectangle::GetRectangle() const
{
	return m_CollisionRect;
}
