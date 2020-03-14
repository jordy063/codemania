#pragma once
#include "structs.h"

//has to be a component I think?
class CollisionRectangle
{
public:
	CollisionRectangle(std::shared_ptr< Rectangle_> rectangle);
	std::shared_ptr< Rectangle_> GetRectangle() const;
private:
	std::shared_ptr< Rectangle_> m_CollisionRect;
};

