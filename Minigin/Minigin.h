#pragma once
#include "TextObject.h"
#include "Player.h"
struct SDL_Window;

class InputObserver;
namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();

	private:
		std::shared_ptr<Player> avatar;
		std::shared_ptr<Player> avatar2;
		std::shared_ptr<InputObserver> pInputObserver;

	};
}