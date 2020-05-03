#pragma once
#include "Entity.h"
#include "TileMapLoader.h"
#include "Command.h"
#include "GameObject.h"

class Player;
namespace comps
{
	class BoundingBoxComponent;
	class PhysicsComponent;
	class SpriteComponent;
}
class Enemy : public Entity
{
public:
	Enemy(std::shared_ptr<dae::Scene> scene, int level, int id,bool gravity);
	virtual void CreateComponents(std::shared_ptr<dae::Scene> scene, int level, int id, bool gravity);
	void ClearAI();
	virtual void Update(float elapsedSecs,std::shared_ptr<Player> player) override;

	virtual void SetIsHit() = 0;

protected:
	std::shared_ptr<comps::PhysicsComponent> pPhysicsComp;
	std::shared_ptr<comps::SpriteComponent> pSpriteComp;
	bool AnimationStarted = false;
	comps::Direction m_CurrentDirection;

	//commands
	MoveLeftCommand m_MoveLeftCommand;
	MoveRightCommand m_MoveRightCommand;
	MoveUpCommand m_MoveUpCommand;
	MoveDownCommand m_MoveDownCommand;
	float2 m_Speed;
private:


	std::map<comps::Direction, int> DirToRow;

	static int m_Seed;
	bool m_IsAlive;



	

};
