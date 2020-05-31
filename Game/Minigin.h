#pragma once
#include "Player.h"
#include "Ghost.h"
#include "Menu.h"

struct SDL_Window;

class EnemyManager;
class InputObserver;
class Menu;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame();
		void Update(float elapsedSecs);
		void Cleanup();
		void Run();

	private:
		std::shared_ptr<dae::GameObject> m_pPlayer1;
		std::shared_ptr<dae::GameObject> m_pPlayer2;
		std::shared_ptr<Enemy> m_pEnemy;
		std::shared_ptr<InputObserver> pInputObserver;
		void MakePlayer(int controllerId, int spriteId,Scene& scene, std::shared_ptr<dae::GameObject>& pPlayer, float2 pos);
		void MakeGameAssets();
		GameMode m_GameMode;
		bool m_HasMadeAssets = false;
		
	};
}