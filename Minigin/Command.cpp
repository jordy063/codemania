#include "MiniginPCH.h"
#include "Command.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "GameObject.h"

void MakeBullet(std::shared_ptr<comps::PhysicsComponent> physicsComp, comps::Direction direction, float speed)
{
	auto pos = physicsComp->GetTransform()->GetPosition();
	auto bullet = std::shared_ptr<Bullet>(new Bullet(direction, speed));
	bullet->GetGameObject()->GetTransform()->Translate(pos.x, pos.y);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(bullet->GetGameObject());
}
void changeDirection(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,comps::Direction direction,float speed)
{
	physicsComp->SetMovement(direction,speed);
	int row{};
	switch(direction){ 
	case comps::Direction::LEFT:
		row = 3;
		break;

	case comps::Direction::RIGHT:
		row = 1;
		break;

	case comps::Direction::UP:
		row = 2;
		break;

	case comps::Direction::DOWN:
		row = 0;
		break;

	}
	spriteComp->SetActiveRow(row);
}
void StopMoving(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	physicsComp->SetSpeed(speed);
	spriteComp->SetActiveRowStop();
}
void MoveLeftCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	changeDirection(physicsComp, spriteComp,comps::Direction::LEFT,speed);

}
void MoveRightCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::RIGHT,speed);
}
void MoveUpCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::UP,speed);
}
void MoveDownCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::DOWN,speed);
}
void StopMovingCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	StopMoving(physicsComp, spriteComp,speed);
}

void ShootRightCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::RIGHT, speed);

}

void ShootUpCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::UP, speed);
}

void ShootDownCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::DOWN, speed);
}

void ShootLeftCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::LEFT, speed);
}
