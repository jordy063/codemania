#pragma once
#include "structs.h"

//has to be a component I think?
class CollisionRectangle
{
public:
	CollisionRectangle(rectangle_* rectangle);
	std::shared_ptr< rectangle_> GetRectangle() const;
private:
	std::shared_ptr< rectangle_> m_CollisionRect;
};

