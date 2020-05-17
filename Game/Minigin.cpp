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
#include "BulletManager.h"
#include "BoundingBoxComponent.h"
#include "GhostAIComponent.h"
#include "HealthComponent.h"
#include "ZenChanAIComponent.h"
#include "structs.h"
#include "Menu.h"
#include "CollisionComponent.h"
#include "LevelManager.h"



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
		640,
		480,
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

	auto loader = std::shared_ptr<TileMapLoader>(new TileMapLoader(10, { 0,0 }, SceneManager::GetInstance().GetActiveScene()));

	scene.AddTileMap(loader);

	m_pMenu = std::shared_ptr<Menu>(new Menu({ 0,0 }));

	MakePlayer(-1, 0, scene);
	
	/*m_pPlayer = std::shared_ptr<Player>(new Player(-1,0, SceneManager::GetInstance().GetActiveScene()));
	m_pPlayer->GetGameObject()->GetTransform()->Translate(100, 50);
	
	scene.Add(m_pPlayer);


	m_pPlayer2 = std::shared_ptr<Player>(new Player( 1,1, SceneManager::GetInstance().GetActiveScene()));
	m_pPlayer2->GetGameObject()->GetTransform()->Translate(150, 50);*/

	//scene.Add(m_pPlayer2);
	BulletManager::GetInstance().RegisterPlayer(m_pPlayer);
	EnemyManager::GetInstance().RegisterPlayer(m_pPlayer);
	EnemyManager::GetInstance().MakeEnemies(SceneManager::GetInstance().GetActiveScene(), 1);
	
	SoundManager2::GetInstance().Init();
	std::string filename{ "../Sounds/drumloop.wav" };
	SoundManager2::GetInstance().playMusic(filename);


	/*auto background = std::make_shared<GameObject>();
	auto texture1 = new comps::TextureComponent("background.jpg");
	background->AddComponent(texture1);
	scene.AddGameObject(background);*/

	/*auto logo = std::make_shared<GameObject>();
	auto texture2 = new comps::TextureComponent("logo.png");
	
	logo->AddComponent(texture2);
	logo->SetPosition(216, 180);
	scene.AddGameObject(logo);*/

	/*go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.AddGameObject(go);*/

	/*auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<GameObject>();

	auto titleText = new comps::TextComponent("Programming 4 Assignment", font);
	title->AddComponent(titleText);
	title->SetPosition(80, 20);

	scene.Add(title);*/


	scene.Initialize();


	//npc->ClearAI();
}

void dae::Minigin::Update(float elapsedSecs)
{
	UNREFERENCED_PARAMETER(elapsedSecs);
	//EnemyManager::GetInstance().Update(elapsedSecs, m_pPlayer);
	//BulletManager::GetInstance().Update();
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

	{
		
		int frames{};
		float secsPerUpdate{ 0.002f };
		float secsPerRender{ 1.0f/30 };
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		float lag{ 0.0f };
		float lag_render{ 0.0f };
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			/*if (menu) {
				Meneumanager.Render();
				Meneumanager.Update();
			}*/
			/*else
			{*/
				auto currentTime = std::chrono::high_resolution_clock::now();
				float elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();
				lastTime = currentTime;
				lag += elapsedSec;
				lag_render += elapsedSec;
				doContinue = input.ProcessInput();


				while (lag > 0)
				{
					//if lag < secperUpdate : update lag, if lag too big, update more than once
					float elapse = min(secsPerUpdate, lag);
					sceneManager.Update(elapse);
					Update(elapse);
					lag -= elapse;
				}

				if (lag_render >= secsPerRender)
				{
					lag_render -= secsPerRender;
					renderer.Render();
					frames++;
				}
			/*}*/
			
		}
	}

	Cleanup();
}

void dae::Minigin::MakePlayer(int controllerId, int spriteId,Scene& scene)
{
	UNREFERENCED_PARAMETER(controllerId);
	UNREFERENCED_PARAMETER(spriteId);
	UNREFERENCED_PARAMETER(scene);
	
	m_pPlayer = std::shared_ptr<dae::GameObject>(new dae::GameObject());
	scene.Add(m_pPlayer);

	float movementSpeed{ 100 };
	auto pPlayerspriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/CharacterSprite.png", 13, 8, spriteId, 0.2f, 32, 32));
	auto pPlayerPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(m_pPlayer->GetTransform(), true, movementSpeed));
	auto pPlayerinputComp = std::shared_ptr<comps::InputComponent>(new comps::InputComponent(pPlayerPhysicsComp, pPlayerspriteComp, controllerId));
	
	auto pPlayerBoundingBoxComp = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(16, 16,pPlayerPhysicsComp));
	auto pPlayerCollisionComp = std::shared_ptr<comps::CollisionComponent>(new comps::CollisionComponent(scene.GetTileMap()->GetCollisionWalls(),
		scene.GetTileMap()->GetCollisionPlatforms(), pPlayerPhysicsComp, pPlayerBoundingBoxComp));
	auto pPlayerHealthComp = std::shared_ptr<comps::HealthComponent>(new comps::HealthComponent(3));


	m_pPlayer->AddComponent(pPlayerspriteComp, ComponentType::SPRITECOMP);
	m_pPlayer->AddComponent(pPlayerHealthComp, ComponentType::HEALTHCOMPONENT);
	m_pPlayer->AddComponent(pPlayerBoundingBoxComp, ComponentType::BOUNDINGBOXCOMP);
	m_pPlayer->AddComponent(pPlayerCollisionComp, ComponentType::COLLISIONCOMPONENT);
	m_pPlayer->AddComponent(pPlayerPhysicsComp, ComponentType::PHYSICSCOMP);

	m_pPlayer->AddComponent(pPlayerinputComp, ComponentType::PLAYERCOMPONENT);

	
	m_pPlayer->GetTransform()->Translate(100, 50);

	LevelManager::GetInstance().RegisterTransformCompLeft(m_pPlayer->GetTransform(), pPlayerCollisionComp);

	////enemy test
	//auto enemyObject = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	//scene.Add(enemyObject);
	//enemyObject->GetTransform()->Translate(150, 100);

	//auto pSpriteComp = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8, 1, 0.2f, 16, 16));
	//auto pPhysicsComp = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(enemyObject->GetTransform(), false, 30.0f));
	//auto pBoundingBox = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene.GetTileMap()->GetCollisionWalls(1),
	//	scene.GetTileMap()->GetCollisionPlatforms(1), pPhysicsComp, 16, 16));
	//auto ghostAiComp = std::shared_ptr<comps::GhostAIComponent>(new comps::GhostAIComponent(m_pPlayer, pSpriteComp, pPhysicsComp, pBoundingBox));

	////add AIcomponent and do the same as in playerclass

	//enemyObject->AddComponent(pSpriteComp, ComponentType::SPRITECOMP);
	//enemyObject->AddComponent(pBoundingBox, ComponentType::BOUNDINGBOXCOMP);
	//enemyObject->AddComponent(pPhysicsComp, ComponentType::PHYSICSCOMP);
	//enemyObject->AddComponent(ghostAiComp, ComponentType::GHOSTAICOMPONENT);

	////enemy test2
	//auto enemyObject2 = std::shared_ptr <dae::GameObject>(new dae::GameObject());
	//scene.Add(enemyObject2);
	//enemyObject2->GetTransform()->Translate(150, 100);

	//auto pSpriteComp2 = std::shared_ptr<comps::SpriteComponent>(new comps::SpriteComponent("../Graphics/Enemies.png", 5, 8, 0, 0.2f, 16, 16));
	//auto pPhysicsComp2 = std::shared_ptr<comps::PhysicsComponent>(new comps::PhysicsComponent(enemyObject2->GetTransform(), true, 30.0f));
	//auto pBoundingBox2 = std::shared_ptr<comps::BoundingBoxComponent>(new comps::BoundingBoxComponent(scene.GetTileMap()->GetCollisionWalls(1),
	//	scene.GetTileMap()->GetCollisionPlatforms(1), pPhysicsComp2, 16, 16));
	//auto pZenChanAiComp = std::shared_ptr<comps::ZenChanAIComponent>(new comps::ZenChanAIComponent(pPlayerBoundingBoxComp, pPlayerHealthComp, pSpriteComp2, pPhysicsComp2, pBoundingBox2,pPlayerPhysicsComp));

	////add AIcomponent and do the same as in playerclass

	//enemyObject2->AddComponent(pSpriteComp2,ComponentType::SPRITECOMP);
	//enemyObject2->AddComponent(pBoundingBox2, ComponentType::BOUNDINGBOXCOMP);
	//enemyObject2->AddComponent(pPhysicsComp2,ComponentType::PHYSICSCOMP);
	//enemyObject2->AddComponent(pZenChanAiComp, ComponentType::ZENCHANCOMPONENT);

	///*auto test = m_pPlayer->GetComponent(ComponentType::SPRITECOMP);
	//auto test2 = std::dynamic_pointer_cast<comps::SpriteComponent>(test);
	//test2->SetActiveRow(3);
	//
	//UNREFERENCED_PARAMETER(test);*/
}
