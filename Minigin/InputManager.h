#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>

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
		void Notify(SDL_Event e);


	private:
		XINPUT_STATE currentState{};
		std::shared_ptr<InputObserver> pInputObserver;
	};

}
