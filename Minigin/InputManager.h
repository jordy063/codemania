#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
#include <map>


class InputObserver;
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
		void Register(std::shared_ptr<InputObserver> inputObserver);
		void NotifyInput(SDL_Event e, bool move);
		void NotifyInputController(WORD e, bool move);
		void checkButtons();

	private:
		XINPUT_STATE currentState{};
		//InputObserver* pInputObserver;
		std::shared_ptr<InputObserver> pInputObserver;
		bool m_IsShooting = false;
		std::map< WORD, bool> m_ButtonMap{
			std::pair<WORD,bool>{WORD(XINPUT_GAMEPAD_DPAD_UP),false},
		std::pair<WORD,bool>{WORD(XINPUT_GAMEPAD_DPAD_RIGHT),false},
		std::pair<WORD,bool>{WORD(XINPUT_GAMEPAD_DPAD_DOWN),false},
		std::pair<WORD,bool>{WORD(XINPUT_GAMEPAD_DPAD_LEFT),false},
		std::pair<WORD,bool>{WORD(XINPUT_GAMEPAD_A),false}
		};
	};
}


