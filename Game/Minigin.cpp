#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Logger.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "InputObserver.h"
#include "Enemy.h"
#include "XboxController.h"
#include "TileMapLoader.h"
//#include "SoundManager.h"
#include "SoundManager2.h"
#include "EnemyManager.h"
#include "BubbleManager.h"
#include "BoundingBoxComponent.h"
#include "GhostAIComponent.h"
#include "HealthComponent.h"
#include "ZenChanAIComponent.h"
#include "structs.h"
#include "Menu.h"
#include "CollisionComponent.h"
#include "LevelManager.h"
#include "ItemManager.h"
#include "Menu.h"
#include "UI.h"
#include "BoulderManager.h"
#include <thread>
#include "PlayerVersusComponent.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		600,
		630,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);

	
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame()
{
	

	std::string sceneName{ "Bubble Bobble Scene" };
	auto& scene{ SceneManager::GetInstance().CreateScene(sceneName) };

	auto loader{ std::shared_ptr<TileMapLoader>(new TileMapLoader(10, { 0,30 }, SceneManager::GetInstance().GetActiveScene())) };

	scene.AddTileMap(loader);

	MakePlayer(-1, 0, scene, m_pPlayers, { 100,70 },true);
	MakePlayer(-2, 1, scene, m_pPlayers, { 200,70 },false);
	MakeEnemyPlayer(-2, 2, scene, m_pPlayers, { 300,70 });
	
	
	SoundManager2::GetInstance().Init();
	std::string filename{ "../Sounds/drumloop.wav" };
	SoundManager2::GetInstance().playMusic(filename);

	LevelManager::GetInstance().Initialize(scene);

	Menu::GetInstance().RegisterPlayer2(m_pPlayers[1]);

	InitializeUI();

	scene.Initialize();
	Menu::GetInstance().Initialize();

	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/scores.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/items.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/Bubble.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/boulders.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/ItemSheet.png");
}

void dae::Minigin::Update(float elapsedSecs)
{

	
	LevelManager::GetInstance().Update( elapsedSecs);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
	std::thread update(&dae::Minigin::RunMainUpdate,this);

	RunMainRender();
	
	update.join();
	Cleanup();
}

void dae::Minigin::MakePlayer(int controllerId, int spriteId,Scene& scene,std::vector<std::shared_ptr<dae::GameObject>>& pPlayerVector,float2 pos,bool isPlayerOne)
{
	UNREFERENCED_PARAMETER(controllerId);
	UNREFERENCED_PARAMETER(spriteId);
	UNREFERENCED_PARAMETER(scene);
	
	auto pPlayer = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	scene.Add(pPlayer);

	float movementSpeed{ 100 };
	auto pPlayerspriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/CharacterSprite.png", 13, 8, spriteId, 0.2f, 44, 22));
	auto pPlayerPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(pPlayer->GetTransform(), true, movementSpeed));
	auto pPlayerinputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(pPlayerPhysicsComp, pPlayerspriteComp, controllerId));
	
	auto pPlayerBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22,pPlayerPhysicsComp));
	auto pPlayerCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene.GetTileMap()->GetCollisionWalls(),
		scene.GetTileMap()->GetCollisionPlatforms(), pPlayerPhysicsComp, pPlayerBoundingBoxComp));
	auto pPlayerHealthComp = std::shared_ptr<comps::HealthComponent>(new comps::HealthComponent(4));


	pPlayer->AddComponent(pPlayerspriteComp, ComponentType::SPRITECOMP);
	pPlayer->AddComponent(pPlayerHealthComp, ComponentType::HEALTHCOMPONENT);
	pPlayer->AddComponent(pPlayerBoundingBoxComp, ComponentType::BOUNDINGBOXCOMP);
	pPlayer->AddComponent(pPlayerCollisionComp, ComponentType::COLLISIONCOMPONENT);
	pPlayer->AddComponent(pPlayerPhysicsComp, ComponentType::PHYSICSCOMP);

	pPlayer->AddComponent(pPlayerinputComp, ComponentType::INPUTCOMPONENT);

	
	pPlayer->GetTransform()->Translate(pos.x, pos.y);

	if(isPlayerOne)
	LevelManager::GetInstance().RegisterTransformCompLeft(pPlayer->GetTransform(), pPlayerCollisionComp);
	else
		LevelManager::GetInstance().RegisterTransformCompRight(pPlayer->GetTransform(), pPlayerCollisionComp);

	pPlayerVector.push_back(pPlayer);


}

void dae::Minigin::MakeEnemyPlayer(int controllerId, int spriteId, Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& pPlayerVector, float2 pos)
{
	UNREFERENCED_PARAMETER(controllerId);
	UNREFERENCED_PARAMETER(spriteId);
	UNREFERENCED_PARAMETER(scene);

	auto pPlayer = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	scene.Add(pPlayer);

	float movementSpeed{ 100 };
	auto pPlayerspriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/EnemySheet.png", 6, 8, spriteId, 0.2f, 44, 22));
	auto pPlayerHealthComp = std::shared_ptr<comps::HealthComponent>(new comps::HealthComponent(4));
	auto pPlayerVersusComponent = std::shared_ptr<comps::PlayerVersusComponent>(new comps::PlayerVersusComponent(m_pPlayers));
	auto pPlayerPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(pPlayer->GetTransform(), true, movementSpeed));
	auto pPlayerinputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(pPlayerPhysicsComp, pPlayerspriteComp, controllerId));

	auto pPlayerBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22, pPlayerPhysicsComp));
	auto pPlayerCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene.GetTileMap()->GetCollisionWalls(),
		scene.GetTileMap()->GetCollisionPlatforms(), pPlayerPhysicsComp, pPlayerBoundingBoxComp));
	
	
	
	pPlayer->AddComponent(pPlayerHealthComp, ComponentType::HEALTHCOMPONENT);
	pPlayer->AddComponent(pPlayerspriteComp, ComponentType::SPRITECOMP);
	pPlayer->AddComponent(pPlayerVersusComponent, ComponentType::PLAYERVERSUSCOMPONENT);
	pPlayer->AddComponent(pPlayerBoundingBoxComp, ComponentType::BOUNDINGBOXCOMP);
	pPlayer->AddComponent(pPlayerCollisionComp, ComponentType::COLLISIONCOMPONENT);
	pPlayer->AddComponent(pPlayerPhysicsComp, ComponentType::PHYSICSCOMP);
	pPlayer->AddComponent(pPlayerinputComp, ComponentType::INPUTCOMPONENT);

	

	pPlayerspriteComp->SetBeginEndFrames(32, 39);
	pPlayer->GetTransform()->Translate(pos.x, pos.y);



	pPlayerVector.push_back(pPlayer);

}

void dae::Minigin::RegisterPlayersInManager()
{
	BubbleManager::GetInstance().RegisterPlayers(m_pPlayers);
	EnemyManager::GetInstance().RegisterPlayers(m_pPlayers);
	ItemManager::GetInstance().RegisterPlayers(m_pPlayers);
	BoulderManager::GetInstance().RegisterPlayers(m_pPlayers);
	LevelManager::GetInstance().SetAmountOfPlayers(int(m_pPlayers.size()));
	
}

void dae::Minigin::SpawnEnemies()
{
	EnemyManager::GetInstance().MakeEnemies(SceneManager::GetInstance().GetActiveScene(), 0);
}

void dae::Minigin::InitializeUI()
{
	m_pUI = std::shared_ptr<UI>(new UI(m_pPlayers));
	m_pUI->Initialize();
}

void dae::Minigin::RemovePlayer(bool isVersus)
{
	if (isVersus)
	{
		m_pPlayers[2].swap(m_pPlayers[1]);

		//register components in the levelmanager
		auto pPlayerCollisionComp = m_pPlayers[1]->GetComponent(ComponentType::COLLISIONCOMPONENT);
		auto playerCollisionComp = std::dynamic_pointer_cast<comps::CollisionComponent>(pPlayerCollisionComp);

		LevelManager::GetInstance().RegisterTransformCompRight(m_pPlayers[1]->GetTransform(), playerCollisionComp);
	}

	m_pPlayers[2]->Clear();
	m_pPlayers.pop_back();




}

void dae::Minigin::RemovePlayers()
{
	m_pPlayers[2]->Clear();
	m_pPlayers.pop_back();
	m_pPlayers[1]->Clear();
	m_pPlayers.pop_back();
}

void dae::Minigin::MakeGameAssets()
{
	//get mode

	//depending on the mode we might do different things.

	auto inputComp1{ m_pPlayers[0]->GetComponent(ComponentType::INPUTCOMPONENT) };
	auto actualInputComp1 = std::dynamic_pointer_cast<comps::InputComponent>(inputComp1);

	//make the oberserver for the player

	auto inputComp2{ m_pPlayers[1]->GetComponent(ComponentType::INPUTCOMPONENT) };
	auto actualInputComp2 = std::dynamic_pointer_cast<comps::InputComponent>(inputComp2);

	auto inputComp3{ m_pPlayers[2]->GetComponent(ComponentType::INPUTCOMPONENT) };
	auto actualInputComp3 = std::dynamic_pointer_cast<comps::InputComponent>(inputComp3);
	bool useControllers{ Menu::GetInstance().GetUseControllers() };

	switch (Menu::GetInstance().GetGameMode())
	{
	case GameMode::SINGLEPLAYER:
		if (useControllers)
		{
			actualInputComp1->MakeObserver(0);
		}
		else
		{
			actualInputComp1->MakeObserver(-1);

		}
		RemovePlayers();
		RegisterPlayersInManager();
		SpawnEnemies();
		break;
	case GameMode::MULTIPLAYER:
		
		if (useControllers)
		{
			actualInputComp1->MakeObserver(0);
			actualInputComp2->MakeObserver(1);
		}
		else
		{
			actualInputComp1->MakeObserver(-1);
			actualInputComp2->MakeObserver(-2);
		}
		RemovePlayer(false);
		RegisterPlayersInManager();
		SpawnEnemies();
		m_pUI->AddPlayer2();
		break;
	case GameMode::VERSUS:
		
		if (useControllers)
		{
			actualInputComp1->MakeObserver(0);
			actualInputComp3->MakeObserver(1);
		}
		else
		{
			actualInputComp1->MakeObserver(-1);
			actualInputComp3->MakeObserver(-2);
		}
		RemovePlayer(true);
		RegisterPlayersInManager();
		m_pUI->AddPlayer2();
		//change the nessecary things
		break;
	}

	

	
}

void dae::Minigin::RunMainUpdate()
{
	//float secsPerUpdate{ 0.002f };
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag{ 0.0f };
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& menu = Menu::GetInstance();



	while (m_DoContinue)
	{
		
		//we calculated the lagg
		auto currentTime = std::chrono::high_resolution_clock::now();
		float elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += elapsedSec;
	
		m_DoContinue = input.ProcessInput();

		auto gameState = InputManager::GetInstance().GetGameState();
		UNREFERENCED_PARAMETER(sceneManager);

		//if it's bigger than 0 we update

		
			//if lag < secperUpdate : update lag, if lag too big, update more than once
		

		float elapse = lag;

		
		switch (gameState)
		{
		case dae::MainMenu:
			menu.Update();

			if (menu.GetIsQuitCalled())
			{
				m_DoContinue = false;
			}
			break;
		case dae::Playing:
			if (m_HasMadeAssets)
			{
				sceneManager.Update(elapse);
				Update(elapse);
			}
			break;
		case dae::GameOverMenu:
			break;
		case dae::EndMenu:
			break;
		default:
			break;
		}
		lag -= elapse;
		
	}

}

void dae::Minigin::RunMainRender()
{

	int frames{};
	//float secsPerRender{ 1.0f / 300 };
	auto lastTime = std::chrono::high_resolution_clock::now();
	auto& renderer = Renderer::GetInstance();
	float lag_render{ 0.0f };
	auto& menu = Menu::GetInstance();

	
	while (m_DoContinue)
	{

		//we calculated the lagg
		auto currentTime = std::chrono::high_resolution_clock::now();
		float elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag_render += elapsedSec;
		
		InputManager::GetInstance().FillEventQueue();

		auto gameState = InputManager::GetInstance().GetGameState();
		//if it's bigger than 0 we update


		
		switch (gameState)
		{
		case dae::MainMenu:
			menu.Render();
			break;
		case dae::Playing:
			if (m_HasMadeAssets == false)
			{
				m_HasMadeAssets = true;
				MakeGameAssets();
			}
			renderer.Render();
			break;
		case dae::GameOverMenu:
			break;
		case dae::EndMenu:
			break;
		default:
			break;
		}

		frames++;
		
	}
}
