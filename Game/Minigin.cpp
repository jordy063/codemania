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
#include "XboxController.h"
#include "TileMapLoader.h"
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
#include "GameOverMenu.h"
#include "EndLevelMenu.h"
#include "GameInfo.h"
#include "ScoreBoard.h"
#include "EnemyObserver.h"


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

	MakePlayer(-1, 0, m_pPlayers, { 100,70 },true);
	MakePlayer(-2, 1, m_pPlayers, { 200,70 },false);
	MakeEnemyPlayer(-2, 2, m_pPlayers, { 300,70 });
	
	
	SoundManager2::GetInstance().Init();
	

	LevelManager::GetInstance().Initialize(scene);

	Menu::GetInstance().RegisterPlayer2(m_pPlayers[1]);

	InitializeUI();

	scene.Initialize();
	Menu::GetInstance().Initialize();
	GameOverMenu::GetInstance().Initialize();
	EndLevelMenu::GetInstance().Initialize();

	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/scores.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/items.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/Bubble.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/boulders.png");
	dae::ResourceManager::GetInstance().LoadTexture("../Graphics/ItemSheet.png");
}

void dae::Minigin::Update(float elapsedSecs)
{
	auto& sceneManager = SceneManager::GetInstance();
	auto& menu = Menu::GetInstance();
	auto& gameOverMenu = GameOverMenu::GetInstance();
	auto& endLevelMenu = EndLevelMenu::GetInstance();
	

	auto gameState = GameInfo::GetInstance().GetGameState();
	switch (gameState)
	{
	case MAINMENU:
		menu.Update(elapsedSecs);

		if (menu.GetIsQuitCalled())
		{
			m_DoContinue = false;
		}
		break;
	case PLAYING:
		if (m_HasMadeAssets == false)
		{
			m_HasMadeAssets = true;
			MakeGameAssets();
		}
		else
		{
			sceneManager.Update(elapsedSecs);
			LevelManager::GetInstance().Update(elapsedSecs);
		}
		if (LevelManager::GetInstance().GetCurrentLevel() == 3)
			GameInfo::GetInstance().SetGameState(GameState::ENDLEVELMENU);
		break;
	case GAMEOVERMENU:
		gameOverMenu.Update();
		if (gameOverMenu.GetIsQuitCalled())
		{
			m_DoContinue = false;
		}

		break;
	case ENDLEVELMENU:
		endLevelMenu.Update();
		if (endLevelMenu.GetIsQuitCalled())
		{
			m_DoContinue = false;
		}
		break;
	case RESET:
		ResetGame();
	default:
		break;
	}
	//LevelManager::GetInstance().Update( elapsedSecs);

}

void dae::Minigin::render() const
{
	auto& menu = Menu::GetInstance();
	auto& gameOverMenu = GameOverMenu::GetInstance();
	auto& endLevelMenu = EndLevelMenu::GetInstance();
	auto& renderer = Renderer::GetInstance();
	InputManager::GetInstance().FillEventQueue();

	auto gameState = GameInfo::GetInstance().GetGameState();
	switch (gameState)
	{
	case MAINMENU:
		menu.Render();
		break;
	case PLAYING:
		renderer.Render();
		break;
	case GAMEOVERMENU:
		gameOverMenu.Render();
		break;
	case ENDLEVELMENU:
		endLevelMenu.Render();
		break;
	default:
		break;
	}
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

void dae::Minigin::MakePlayer(int controllerId, int spriteId,std::vector<std::shared_ptr<dae::GameObject>>& pPlayerVector,float2 pos,bool isPlayerOne)
{
	UNREFERENCED_PARAMETER(controllerId);
	UNREFERENCED_PARAMETER(spriteId);
	
	auto pPlayer = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	SceneManager::GetInstance().GetActiveScene()->Add(pPlayer);

	float movementSpeed{ 100 };
	auto pPlayerspriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/CharacterSprite.png", 13, 8, spriteId, 0.2f, 44, 22));
	auto pPlayerPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(pPlayer->GetTransform(), true, movementSpeed));
	auto pPlayerinputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(pPlayerPhysicsComp, pPlayerspriteComp, controllerId));
	
	auto pPlayerBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22,pPlayerPhysicsComp));
	auto pPlayerCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), pPlayerPhysicsComp, pPlayerBoundingBoxComp));
	auto pPlayerHealthComp = std::shared_ptr<comps::HealthComponent>(new comps::HealthComponent(4, !isPlayerOne));


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

void dae::Minigin::MakeEnemyPlayer(int controllerId, int spriteId, std::vector<std::shared_ptr<dae::GameObject>>& pPlayerVector, float2 pos)
{
	UNREFERENCED_PARAMETER(controllerId);
	UNREFERENCED_PARAMETER(spriteId);

	auto pPlayer = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	SceneManager::GetInstance().GetActiveScene()->Add(pPlayer);
	

	float movementSpeed{ 100 };
	auto pPlayerspriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/EnemySheet.png", 6, 8, spriteId, 0.2f, 44, 22));
	auto pPlayerHealthComp = std::shared_ptr<comps::HealthComponent>(new comps::HealthComponent(4,1));
	
	auto pPlayerPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(pPlayer->GetTransform(), true, movementSpeed));
	auto pPlayerinputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(pPlayerPhysicsComp, pPlayerspriteComp, controllerId));

	auto pPlayerBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(22, 22, pPlayerPhysicsComp));
	auto pPlayerCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionWalls(),
		SceneManager::GetInstance().GetActiveScene()->GetTileMap()->GetCollisionPlatforms(), pPlayerPhysicsComp, pPlayerBoundingBoxComp));
	auto pPlayerVersusComponent = std::shared_ptr<comps::PlayerVersusComponent>(new comps::PlayerVersusComponent(m_pPlayers[0], pPlayerBoundingBoxComp, pPlayerHealthComp));
	
	
	
	pPlayer->AddComponent(pPlayerHealthComp, ComponentType::HEALTHCOMPONENT);
	pPlayer->AddComponent(pPlayerspriteComp, ComponentType::SPRITECOMP);
	pPlayer->AddComponent(pPlayerBoundingBoxComp, ComponentType::BOUNDINGBOXCOMP);
	
	pPlayer->AddComponent(pPlayerCollisionComp, ComponentType::COLLISIONCOMPONENT);
	pPlayer->AddComponent(pPlayerPhysicsComp, ComponentType::PHYSICSCOMP);
	pPlayer->AddComponent(pPlayerinputComp, ComponentType::INPUTCOMPONENT);


	pPlayer->AddComponent(pPlayerVersusComponent, ComponentType::PLAYERVERSUSCOMPONENT);

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
	m_pUI = std::shared_ptr<UI>(new UI(m_pPlayers[0]));
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

	switch (GameInfo::GetInstance().GetGameMode())
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
		m_pUI->AddPlayer2(m_pPlayers[1]);
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
		m_pUI->AddPlayer2(m_pPlayers[1]);
		//change the nessecary things
		break;
	}
	if (SoundManager2::GetInstance().isPlaying() == false)
	{
		std::string filename{ "../Sounds/levelSong.wav" };
		SoundManager2::GetInstance().playMusic(filename);
	}

	EnemyObserver::GetInstance().RegistersPlayerHealthComps(m_pPlayers);
}

void dae::Minigin::RunMainUpdate()
{
	//float secsPerUpdate{ 0.002f };
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag{ 0.0f };
	auto& input = InputManager::GetInstance();


	while (m_DoContinue)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//we calculated the lagg
		auto currentTime = std::chrono::high_resolution_clock::now();
		float elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += elapsedSec;
	
		m_DoContinue = input.ProcessInput();
		

		float elapse = lag;

		Update(elapse);
		
		lag -= elapse;
		
	}

}

void dae::Minigin::RunMainRender()
{

	//we don't have to pass elapsedSecs as the render is const anyway so checks only happen in the update
	while (m_DoContinue)
	{

		render();

	}
}

void dae::Minigin::ResetGame()
{
	clearPlayers();
	m_pUI->Reset();

	//reset gamestate
	GameInfo::GetInstance().SetGameState(GameState::MAINMENU);

	//reset controls
	InputManager::GetInstance().ResetPlayerControl();

	//reset players in bulletmanager
	BubbleManager::GetInstance().Reset();
	//remove enemies
	EnemyManager::GetInstance().RemoveEnemies();
	//reset menu
	Menu::GetInstance().ResetMenu();
	//resetLevelManager
	
	//reset Scoreboard
	ScoreBoard::GetInstance().ResetScore();
	m_HasMadeAssets = false;

	EnemyObserver::GetInstance().Reset();

	ResetLevelManager();
	
}

void dae::Minigin::clearPlayers()
{
	
	auto gameMode = GameInfo::GetInstance().GetGameMode();
	switch (gameMode)
	{
	case SINGLEPLAYER:
		//make enemy + normal player
		MakePlayer(-2, 1, m_pPlayers, { 200,70 }, false);
		MakeEnemyPlayer(-2, 2, m_pPlayers, { 300,70 });

		break;
	case MULTIPLAYER:
		//make enemyplayer
		MakeEnemyPlayer(-2, 2, m_pPlayers, { 300,70 });
		break;
	case VERSUS:
		//make player2
		MakePlayer(-2, 1, m_pPlayers, { 200,70 }, false);
		m_pPlayers[2].swap(m_pPlayers[1]);
		break;
	default:
		break;
	}
}

void dae::Minigin::ResetLevelManager()
{
	LevelManager::GetInstance().Reset();

	auto pPlayerCollisionComp = m_pPlayers[1]->GetComponent(ComponentType::COLLISIONCOMPONENT);
	auto playerCollisionComp = std::dynamic_pointer_cast<comps::CollisionComponent>(pPlayerCollisionComp);

	LevelManager::GetInstance().RegisterTransformCompRight(m_pPlayers[1]->GetTransform(), playerCollisionComp);

}

void dae::Minigin::ResetHealth()
{
	
	for (std::shared_ptr<dae::GameObject> pPlayer : m_pPlayers)
	{
		auto pPlayerHealthComp = pPlayer->GetComponent(ComponentType::HEALTHCOMPONENT);
		auto playerHealthComp = std::dynamic_pointer_cast<comps::HealthComponent>(pPlayerHealthComp);

		playerHealthComp->ResetHealth();
	}
}
