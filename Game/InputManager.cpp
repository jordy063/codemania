#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputObserver.h"
#include "InputComponent.h"
#include "XboxController.h"



bool dae::InputManager::ProcessInput()
{
	
	//check the buttons for every inputobserver
	for (std::map<int, std::vector<std::shared_ptr<InputBaseObserver>>>::iterator iter = pInputObserver.begin(); iter != pInputObserver.end(); ++iter)
	{
		int k = iter->first;
		if (k != -1)
		{
			checkButtons(k);
		}
	}

	SDL_Event e;
	
	//if the queue isn't empty we check if anything is pressed
	//we have seperate notifies for key up and keydown to stop moving if we don't press anything
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

void dae::InputManager::Register(std::shared_ptr<InputBaseObserver> inputObserver,int controllerId)
{
	// contains
	pInputObserver[controllerId].push_back( inputObserver);
}
void dae::InputManager::NotifyInput(SDL_Event e,bool move)
{
	//if the observer with the controller id isn't empty we check what we should do
	// -1 and -2 are keyboard
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

	xboxController xbox(controllerId);

	
	xbox.getState();
	WORD words[5]{ 1,2,4,8,4096 };

	//go over all buttons and only add them if they aren't in the map yet
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
	//if the observer with the controller id isn't empty we check what we should do
	if (!pInputObserver[controllerId].empty())
	{
		for (auto inputObserver : pInputObserver[controllerId]) {
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

void dae::InputManager::ResetPlayerControl()
{
	pInputObserver[-2].clear();
	pInputObserver[0].clear();
	pInputObserver[1].clear();
}
