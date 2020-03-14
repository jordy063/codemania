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
			NotifyInput(e,true);
		}
		if (e.type == SDL_KEYUP) {
			NotifyInput(e,false);
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
void dae::InputManager::Register(std::shared_ptr<InputObserver> inputObserver)
{
	pInputObserver = inputObserver;
}
void dae::InputManager::NotifyInput(SDL_Event e,bool move)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_z:
		pInputObserver->Update(comps::Direction::UP, move);
		break;
	case SDLK_s:
		pInputObserver->Update(comps::Direction::DOWN, move);
		break;
	case SDLK_d:
		pInputObserver->Update(comps::Direction::RIGHT, move);
		break;
	case SDLK_q:
		pInputObserver->Update(comps::Direction::LEFT, move);
		break;
	case SDLK_e:
		if (move && !m_IsShooting)
		{
			pInputObserver->ShootUpdate();
			m_IsShooting = true;
		}
		if (!move)
		{
			m_IsShooting = false;
		}
		
	}

}

