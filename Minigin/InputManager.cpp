#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputObserver.h"
#include "InputComponent.h"
#include "XboxController.h"
#include "Audio.h"



bool dae::InputManager::ProcessInput()
{
	


	//DWORD dwResult;
	//for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	//{


	//	ZeroMemory(&currentState, sizeof(XINPUT_STATE));

	//	// Simply get the state of the controller from XInput.
	//	dwResult = XInputGetState(i, &currentState);

	//	if (dwResult == ERROR_SUCCESS)
	//	{
	//		// Controller is connected 
	//		std::cout << "Button A has been pressed" << std::endl;
	//	}
	//	else
	//	{
	//		// Controller is not connected 

	//	}
	//}
	checkButtons();

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

	//ServiceLocator::GetAudio();
	//Audio* test;
	//test->PlaySound()
	//service->RegisterAudioService()


}
void dae::InputManager::checkButtons()	
{
	//if(currentState.Gamepad.wButtons)
	//if (IsPressed(ControllerButton::ButtonA))
	//{
	//	std::cout << "Button A has been pressed" << std::endl;
	//}	
	//else if (IsPressed(ControllerButton::ButtonB))
	//	std::cout << "Button B has been pressed" << std::endl;
	//else if (IsPressed(ControllerButton::ButtonY))
	//	std::cout << "Button Y has been pressed" << std::endl;
	//else if (IsPressed(ControllerButton::ButtonX))
	//{
	//	std::cout << "Button X has been pressed" << std::endl;
	//}

	xboxController xbox(0);

	
	xbox.getState();
	for (std::map<WORD, bool>::iterator iter = m_ButtonMap.begin(); iter != m_ButtonMap.end(); ++iter)
	{
		WORD k = iter->first;
		bool isPressed{ xbox.checkButtonPress(k) };
		if (isPressed != m_ButtonMap[k])
		{
			NotifyInputController(k, isPressed);

			m_ButtonMap[k] = isPressed;
		}
	}
}
void dae::InputManager::NotifyInputController(WORD e, bool move)
{
	switch (e)
	{
	case XINPUT_GAMEPAD_DPAD_UP:
		pInputObserver->Update(comps::Direction::UP, move);

		break;
	case XINPUT_GAMEPAD_DPAD_DOWN:
		pInputObserver->Update(comps::Direction::DOWN, move);
		break;
	case XINPUT_GAMEPAD_DPAD_RIGHT:
		pInputObserver->Update(comps::Direction::RIGHT, move);
		break;
	case XINPUT_GAMEPAD_DPAD_LEFT:
		pInputObserver->Update(comps::Direction::LEFT, move);
		break;
	case XINPUT_GAMEPAD_A:
		if (move)
		{
			pInputObserver->ShootUpdate();
		}
		

	}

	//ServiceLocator::GetAudio();
	//Audio* test;
	//test->PlaySound()
	//service->RegisterAudioService()


}
