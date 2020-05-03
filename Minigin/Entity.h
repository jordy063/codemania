#pragma once
//#include "InputManager.h"
#include "structs.h"

namespace dae
{
	class GameObject;
}
class Player;
namespace comps
{
	class BoundingBoxComponent;
}
class Entity
{
public:
	Entity();
	~Entity();

	Entity(const Entity& other) = delete;
	Entity(Entity&& other) noexcept = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity& operator=(Entity&& other) noexcept = delete;


	virtual void Initialize();

	virtual void Update(float elapsedSecs, std::shared_ptr<Player> player);
	void Render();

	rectangle_ GetBoundingBox() const;
	std::shared_ptr<dae::GameObject> GetGameObject() const { return m_EntityObject; };
	bool IsOverlapping(std::shared_ptr<Entity> subject);

protected:
	std::shared_ptr<comps::BoundingBoxComponent> m_pBoundingBox;
	std::shared_ptr<dae::GameObject> m_EntityObject;
	virtual void CreateComponents();
	void CreateEntityObject();
	void InitializeEntityObject();
	bool m_Alive;
};

