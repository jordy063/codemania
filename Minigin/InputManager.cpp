#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputObserver.h"
#include "InputComponent.h"


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			Notify(e);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{

	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}
void dae::InputManager::Register(InputObserver* inputObserver)
{
	UNREFERENCED_PARAMETER(inputObserver);
	//pInputObserver = inputObserver;
}
void dae::InputManager::Register(std::shared_ptr<InputObserver> inputObserver)
{
	pInputObserver = inputObserver;
}
void dae::InputManager::Notify(SDL_Event e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_z:
		pInputObserver->Update(comps::Direction::UP, 10);
	case SDLK_s:
		pInputObserver->Update(comps::Direction::DOWN, 10);
	case SDLK_d:
		pInputObserver->Update(comps::Direction::RIGHT, 10);
	case SDLK_q:
		pInputObserver->Update(comps::Direction::LEFT, 10);
	}

}
