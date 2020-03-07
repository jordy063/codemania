#include "MiniginPCH.h"
#include "Command.h"

void changeDirection(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp,comps::Direction direction)
{
	physicsComp->SetMovement(direction, physicsComp->GetDefaultSpeed());
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
void StopMoving(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
{
	physicsComp->SetSpeed(0);
	spriteComp->SetActiveRowStop();
}
void MoveLeftCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
{
	changeDirection(physicsComp, spriteComp,comps::Direction::LEFT);

}
void MoveRightCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::RIGHT);
}
void MoveUpCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::UP);
}
void MoveDownCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
{
	changeDirection(physicsComp, spriteComp, comps::Direction::DOWN);
}
void StopMovingCommand::Execute(std::shared_ptr<comps::PhysicsComponent> physicsComp, std::shared_ptr<comps::SpriteComponent> spriteComp)
{
	StopMoving(physicsComp, spriteComp);
}