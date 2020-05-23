#pragma once
#include "InputComponent.h"
#include "InputBaseObserver.h"

class InputObserver final : public InputBaseObserver
{

public:
	InputObserver(comps::InputComponent* inputComp,int controllerId);
	~InputObserver();

	void OnDirectionalKey(comps::Direction direction, bool move) override;
	void OnSelectKey(int spriteId) override;
	/*virtual void Update(comps::Direction direction, bool move);
	virtual void ShootUpdate(int spriteId);*/
private:
	comps::InputComponent* pInputComp;
	comps::Direction m_CurrentDirection;
	int m_ControllerId;
};
