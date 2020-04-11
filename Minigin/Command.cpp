#include "MiniginPCH.h"
#include "Command.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "GameObject.h"

void MakeBullet(std::shared_ptr<comps::PhysicsComponent> physicsComp, comps::Direction direction, float speed)
{
	auto pos = physicsComp->GetTransform()->GetPosition();
	auto bullet = std::shared_ptr<Bullet>(new Bullet(direction, speed,dae::SceneManager::GetInstance().GetActiveScene()));
	
	bullet->GetGameObject()->GetTransform()->Translate(pos.x, pos.y);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(bullet->GetGameObject());
	//dae::SceneManager::GetInstance().GetActiveScene()->
}
void changeDirection(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,comps::Direction direction,float speed)
{
	if (direction == comps::Direction::RIGHT || direction == comps::Direction::LEFT)
	{
		physicsComp->SetSpeedX(direction == comps::Direction::RIGHT ? speed : -speed);
		int row{};
		switch (direction) {
		case comps::Direction::LEFT:
			row = 3;
			break;

		case comps::Direction::RIGHT:
			row = 1;
			break;

		}
		spriteComp->SetActiveRow(row);
	}
	else
	{
		physicsComp->SetSpeedY(direction == comps::Direction::DOWN ? speed : -speed);
	}
}
void StopMoving(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	physicsComp->SetSpeedX(speed);
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
	/*UNREFERENCED_PARAMETER(physicsComp);
	UNREFERENCED_PARAMETER(spriteComp);
	UNREFERENCED_PARAMETER(speed);*/

	if (!physicsComp->GetAirBorne())
	{
		changeDirection(physicsComp, spriteComp, comps::Direction::UP, speed);
	}


}
void MoveDownCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed)
{
	UNREFERENCED_PARAMETER(physicsComp);
	UNREFERENCED_PARAMETER(spriteComp);
	UNREFERENCED_PARAMETER(speed);

	//changeDirection(physicsComp, spriteComp, comps::Direction::DOWN,speed);
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
