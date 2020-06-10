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
	for (std::map<int, std::vector<std::shared_ptr<InputBaseObserver>>>::iterator iter = pInputObserver.begin(); iter != pInputObserver.end(); ++iter)
	{
		int k = iter->first;
		if (k != -1)
		{
			checkButtons(k);
		}
	}

	SDL_Event e;
	
	while (!m_EventQueue.empty()) {
		e = m_EventQueue.front();
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			NotifyInput(e, true);
		}
		if (e.type == SDL_KEYUP) {
			NotifyInput(e, false);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		m_EventQueue.pop();
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
void dae::InputManager::Register(std::shared_ptr<InputBaseObserver> inputObserver,int controllerId)
{
	// contains
	pInputObserver[controllerId].push_back( inputObserver);
}
void dae::InputManager::NotifyInput(SDL_Event e,bool move)
{
	if (!pInputObserver[-1].empty())
	{
		for (auto inputObserver : pInputObserver[-1]) {
			std::cout << e.key.keysym.sym << "," << move << '\n';
			switch (e.key.keysym.sym)
			{
			case SDLK_z:
				inputObserver->OnDirectionalKey(comps::Direction::UP, move);
				break;
			case SDLK_s:
				inputObserver->OnDirectionalKey(comps::Direction::DOWN, move);
				break;
			case SDLK_d:
				inputObserver->OnDirectionalKey(comps::Direction::RIGHT, move);
				break;
			case SDLK_q:
				inputObserver->OnDirectionalKey(comps::Direction::LEFT, move);
				break;
			case SDLK_e:
				inputObserver->OnSelectKey(0);
				if (move && !m_IsShooting)
				{
					
					m_IsShooting = true;
				}
				if (!move)
				{
					m_IsShooting = false;
				}

			}
		}
	}

	if (!pInputObserver[-2].empty())
	{
		for (auto inputObserver : pInputObserver[-2]) {

			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				inputObserver->OnDirectionalKey(comps::Direction::UP, move);
				break;
			case SDLK_DOWN:
				inputObserver->OnDirectionalKey(comps::Direction::DOWN, move);
				break;
			case SDLK_RIGHT:
				inputObserver->OnDirectionalKey(comps::Direction::RIGHT, move);
				break;
			case SDLK_LEFT:
				inputObserver->OnDirectionalKey(comps::Direction::LEFT, move);
				break;
			case SDLK_RETURN:
				if (move && !m_IsShooting)
				{
					inputObserver->OnSelectKey(1);
					m_IsShooting = true;
				}
				if (!move)
				{
					m_IsShooting = false;
				}
			}

		}
	}

	//ServiceLocator::GetAudio();
	//Audio* test;
	//test->PlaySound()
	//service->RegisterAudioService()


}
void dae::InputManager::checkButtons(int controllerId)
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

	xboxController xbox(controllerId);

	
	xbox.getState();
	WORD words[5]{ 1,2,4,8,4096 };
	for (WORD i:words)
	{
		std::pair<int, WORD> k{ controllerId , i};
		bool isPressed{ xbox.checkButtonPress(i) };
		if (m_ButtonMap.count(k) == 0) {
			m_ButtonMap[k] = false;
		}
		if (isPressed != m_ButtonMap[k])
		{
			NotifyInputController(i, isPressed,controllerId);

			m_ButtonMap[k] = isPressed;
		}
	}
}
void dae::InputManager::NotifyInputController(WORD e, bool move,int controllerId)
{
	if (!pInputObserver[-2].empty())
	{
		for (auto inputObserver : pInputObserver[-2]) {
			switch (e)
			{
			case XINPUT_GAMEPAD_DPAD_UP:
				inputObserver->OnDirectionalKey(comps::Direction::UP, move);

				break;
			case XINPUT_GAMEPAD_DPAD_DOWN:
				inputObserver->OnDirectionalKey(comps::Direction::DOWN, move);
				break;
			case XINPUT_GAMEPAD_DPAD_RIGHT:
				inputObserver->OnDirectionalKey(comps::Direction::RIGHT, move);
				break;
			case XINPUT_GAMEPAD_DPAD_LEFT:
				inputObserver->OnDirectionalKey(comps::Direction::LEFT, move);
				break;
			case XINPUT_GAMEPAD_A:
				if (move)
				{
					inputObserver->OnSelectKey(controllerId);
				}


			}
		}
	}
	//ServiceLocator::GetAudio();
	//Audio* test;
	//test->PlaySound()
	//service->RegisterAudioService()


}
void dae::InputManager::DoKeyFunctionality(SDL_Event e, std::shared_ptr<InputBaseObserver> inputObserver,bool move,int id)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_UP:
		inputObserver->OnDirectionalKey(comps::Direction::UP, move);
		break;
	case SDLK_DOWN:
		inputObserver->OnDirectionalKey(comps::Direction::DOWN, move);
		break;
	case SDLK_RIGHT:
		inputObserver->OnDirectionalKey(comps::Direction::RIGHT, move);
		break;
	case SDLK_LEFT:
		inputObserver->OnDirectionalKey(comps::Direction::LEFT, move);
		break;
	case SDLK_RETURN:
		if (move && !m_IsShooting)
		{
			inputObserver->OnSelectKey(id);
			m_IsShooting = true;
		}
		if (!move)
		{
			m_IsShooting = false;
		}
	}
}
void dae::InputManager::DoControllerFunctionality(WORD e, std::shared_ptr<InputBaseObserver> inputObserver, bool move, int controllerId)
{
	switch (e)
	{
	case XINPUT_GAMEPAD_DPAD_UP:
		inputObserver->OnDirectionalKey(comps::Direction::UP, move);

		break;
	case XINPUT_GAMEPAD_DPAD_DOWN:
		inputObserver->OnDirectionalKey(comps::Direction::DOWN, move);
		break;
	case XINPUT_GAMEPAD_DPAD_RIGHT:
		inputObserver->OnDirectionalKey(comps::Direction::RIGHT, move);
		break;
	case XINPUT_GAMEPAD_DPAD_LEFT:
		inputObserver->OnDirectionalKey(comps::Direction::LEFT, move);
		break;
	case XINPUT_GAMEPAD_A:
		if (move)
		{
			inputObserver->OnSelectKey(controllerId);
		}
	}
}

void dae::InputManager::FillEventQueue()
{
	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		m_EventQueue.push(e);
	}
}
