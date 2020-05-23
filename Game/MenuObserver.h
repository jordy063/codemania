#pragma once
#include "InputBaseObserver.h"
class MenuObserver final : public InputBaseObserver
{
public:
	MenuObserver(int controllerId);
	void OnDirectionalKey(comps::Direction direction, bool move) override;
	void OnSelectKey(int spriteId) override;
	
private:
	int m_ControllerId;

};

