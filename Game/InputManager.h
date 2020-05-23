#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
#include <map>


class InputBaseObserver;
namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void Register(std::shared_ptr<InputBaseObserver> inputBaseObserver, int controllerId);
		void NotifyInput(SDL_Event e, bool move);
		void NotifyInputController(WORD e, bool move, int controllerId);
		void checkButtons(int controllerId);

	private:
		XINPUT_STATE currentState{};
		//InputObserver* pInputObserver;
		std::map<int,std::vector<std::shared_ptr<InputBaseObserver>>> pInputObserver;
		bool m_IsShooting = false;
		std::map< std::pair<int, WORD>, bool> m_ButtonMap;
	
	};
}


