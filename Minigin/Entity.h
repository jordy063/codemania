#pragma once
#include "InputManager.h"

namespace dae
{
	class GameObject;
}
class Player;
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

	std::shared_ptr<dae::GameObject> GetGameObject() const { return m_EntityObject; };

protected:
	std::shared_ptr<dae::GameObject> m_EntityObject;
	virtual void CreateComponents();
	void CreateEntityObject();
	void InitializeEntityObject();
	bool m_Alive;
};

