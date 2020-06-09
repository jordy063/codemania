#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
#include <map>
#include <queue>


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
	enum GameState
	{
		MainMenu,
		Playing,
		GameOverMenu,
		EndMenu,
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
		void DoKeyFunctionality(SDL_Event e, std::shared_ptr<InputBaseObserver> inputObserver, bool move, int id);
		void DoControllerFunctionality(WORD e, std::shared_ptr<InputBaseObserver> inputObserver, bool move, int controllerId);
		void SetGameState(GameState gameState);
		GameState GetGameState() const { return m_GameState; }
		void FillEventQueue();
		
	private:
		XINPUT_STATE currentState{};
		GameState m_GameState = MainMenu;
		//InputObserver* pInputObserver;
		std::map<int,std::vector<std::shared_ptr<InputBaseObserver>>> pInputObserver;
		bool m_IsShooting = false;
		std::map< std::pair<int, WORD>, bool> m_ButtonMap;
		std::queue<SDL_Event> m_EventQueue;
	
	};
}


