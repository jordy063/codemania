#pragma once
#include "Player.h"
#include "Ghost.h"

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
		std::shared_ptr<dae::GameObject> m_pPlayer;
		std::shared_ptr<Player> m_pPlayer2;
		std::shared_ptr<Enemy> m_pEnemy;
		std::shared_ptr<InputObserver> pInputObserver;
		std::shared_ptr<Menu> m_pMenu;
		void MakePlayer(int controllerId, int spriteId,Scene& scene);
		
	};
}