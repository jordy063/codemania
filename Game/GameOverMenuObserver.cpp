#include "MiniginPCH.h"
#include "GameOverMenuObserver.h"
#include "GameOverMenu.h"
GameOverMenuObserver::GameOverMenuObserver(int controllerId)
	:InputBaseObserver(controllerId)
{
}

void GameOverMenuObserver::OnDirectionalKey(comps::Direction direction, bool move)
{
	if (move)
	{
		switch (direction)
		{
		case comps::Direction::UP:
			GameOverMenu::GetInstance().MoveUp();
			break;
		case comps::Direction::DOWN:
			GameOverMenu::GetInstance().MoveDown();
			break;
		default:
			break;
		}
	}
}

void GameOverMenuObserver::OnSelectKey(int spriteId)
{
	UNREFERENCED_PARAMETER(spriteId);
	GameOverMenu::GetInstance().Confirm();
}
