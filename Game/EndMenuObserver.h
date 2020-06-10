#pragma once

#include "InputBaseObserver.h"
class EndMenuObserver final : public InputBaseObserver
{
public:
	EndMenuObserver(int controllerId);
	void OnDirectionalKey(comps::Direction direction, bool move) override;
	void OnSelectKey(int spriteId) override;

private:
	int m_ControllerId;

};
