#include "MiniginPCH.h"
#include "EndMenuObserver.h"
#include "EndLevelMenu.h"
EndMenuObserver::EndMenuObserver(int controllerId)
	:InputBaseObserver(controllerId)
{
}

void EndMenuObserver::OnDirectionalKey(comps::Direction direction, bool move)
{
	if (move)
	{
		switch (direction)
		{
		case comps::Direction::UP:
			EndLevelMenu::GetInstance().MoveUp();
			break;
		case comps::Direction::DOWN:
			EndLevelMenu::GetInstance().MoveDown();
			break;
		default:
			break;
		}
	}
}

void EndMenuObserver::OnSelectKey(int spriteId)
{
	UNREFERENCED_PARAMETER(spriteId);
	EndLevelMenu::GetInstance().Confirm();
}