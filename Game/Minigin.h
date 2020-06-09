#pragma once
#include "Player.h"
#include "Ghost.h"
#include "Menu.h"

struct SDL_Window;

class EnemyManager;
class InputObserver;
class Menu;
class UI;

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
		std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
		std::shared_ptr<Enemy> m_pEnemy;
		std::shared_ptr<InputObserver> pInputObserver;
		std::shared_ptr<UI> m_pUI;
		std::shared_ptr<comps::SpriteComponent> m_pPlayer2SpriteComp;
		bool m_DoContinue = true;

		void MakePlayer(int controllerId, int spriteId,Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& pPlayerVector, float2 pos, bool isPlayerOne);
		void MakeEnemyPlayer(int controllerId, int spriteId, Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& pPlayerVector, float2 pos);
		void RegisterPlayersInManager();
		void SpawnEnemies();
		void InitializeUI();
		void RemovePlayer(bool isVersus);
		void RemovePlayers();
		void MakeGameAssets();
		bool m_HasMadeAssets = false;
		void RunMainUpdate();
		void RunMainRender();

		
	};
}