#include "MiniginPCH.h"
#include "MenuObserver.h"
#include "Menu.h"

MenuObserver::MenuObserver(int controllerId)
	:InputBaseObserver(controllerId)
{
}

void MenuObserver::OnDirectionalKey(comps::Direction direction, bool move)
{
	if (move)
	{
		switch (direction)
		{
		case comps::Direction::UP:
			Menu::GetInstance().MoveUp();
			break;
		case comps::Direction::DOWN:
			Menu::GetInstance().MoveDown();
			break;
		case comps::Direction::RIGHT:
			Menu::GetInstance().CheckChangeControllers();
			break;
		case comps::Direction::LEFT:
			Menu::GetInstance().CheckChangeControllers();
			break;
		default:
			break;
		}
	}
}

void MenuObserver::OnSelectKey(int spriteId)
{
	UNREFERENCED_PARAMETER(spriteId);
	Menu::GetInstance().Confirm();
}
