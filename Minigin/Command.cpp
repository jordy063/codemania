#include "MiniginPCH.h"
#include "Command.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "GameObject.h"

void MakeBullet(std::shared_ptr<comps::PhysicsComponent> physicsComp, comps::Direction direction, float speed, int id)
{
	auto pos = physicsComp->GetTransform()->GetPosition();
	auto bullet = std::shared_ptr<Bullet>(new Bullet(direction, speed,dae::SceneManager::GetInstance().GetActiveScene(),id));
	
	bullet->GetGameObject()->GetTransform()->Translate(pos.x, pos.y);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(bullet->GetGameObject());
	//dae::SceneManager::GetInstance().GetActiveScene()->
}
void changeDirection(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,comps::Direction direction,float speed,int id)
{
	if (direction == comps::Direction::RIGHT || direction == comps::Direction::LEFT)
	{
		physicsComp->SetSpeedX(direction == comps::Direction::RIGHT ? speed : -speed);
		int row{};
		switch (direction) {
		case comps::Direction::LEFT:
			row = 1 + id*2;
			break;

		case comps::Direction::RIGHT:
			row = 0 + id*2;
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
void MoveLeftCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed,int id)
{
	changeDirection(physicsComp, spriteComp,comps::Direction::LEFT,speed,id);

}
void MoveRightCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed,int id)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::RIGHT,speed,id);
}
void MoveUpCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	/*UNREFERENCED_PARAMETER(physicsComp);
	UNREFERENCED_PARAMETER(spriteComp);
	UNREFERENCED_PARAMETER(speed);*/

	if (!physicsComp->GetAirBorne() || physicsComp->GetGravityEnabled() == false)
	{
		changeDirection(physicsComp, spriteComp, comps::Direction::UP, speed,id);
	}


}
void MoveDownCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	UNREFERENCED_PARAMETER(physicsComp);
	UNREFERENCED_PARAMETER(spriteComp);
	UNREFERENCED_PARAMETER(speed);
	UNREFERENCED_PARAMETER(id);

	//changeDirection(physicsComp, spriteComp, comps::Direction::DOWN,speed);
}
void StopMovingCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	UNREFERENCED_PARAMETER(id);
	StopMoving(physicsComp, spriteComp,speed);
}

void ShootRightCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	UNREFERENCED_PARAMETER(spriteComp);
	spriteComp->SetBeginEndFrames(33 + id * 16 *2, 47 + id * 16 *2);
	MakeBullet(physicsComp, comps::Direction::RIGHT, speed,id);

}

void ShootUpCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::UP, speed,id);
}

void ShootDownCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::DOWN, speed,id);
}

void ShootLeftCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp, float speed, int id)
{
	
	spriteComp->SetBeginEndFrames(48 + id*16*2, 63 + id*16*2);
	UNREFERENCED_PARAMETER(spriteComp);
	MakeBullet(physicsComp, comps::Direction::LEFT, speed,id);
}
