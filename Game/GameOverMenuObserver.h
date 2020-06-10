#pragma once
#include "InputBaseObserver.h"
class GameOverMenuObserver final : public InputBaseObserver
{
public:
	GameOverMenuObserver(int controllerId);
	void OnDirectionalKey(comps::Direction direction, bool move) override;
	void OnSelectKey(int spriteId) override;

private:
	int m_ControllerId;

};