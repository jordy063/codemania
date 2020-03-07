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
	std::string test{ "demooo" };
	auto& scene = SceneManager::GetInstance().CreateScene(test);

	avatar = std::shared_ptr<Player>(new Player());
	avatar->GetGameObject()->GetTransform()->Translate(100, 100);
	

	scene.Add(avatar);


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
		float SecsPerUpdate{ 0.002f };
		float SecsPerRender{ 1.0f/30 };
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		float lag{ 0.0f };
		float lag_render{ 0.0f };
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += elapsedSec;
			lag_render += elapsedSec;
			doContinue = input.ProcessInput();
			

			while (lag > 0)
			{
				//if lag < secperUpdate : update lag, if lag too big, update more than once
				float elapse = min(SecsPerUpdate, lag);
				sceneManager.Update(elapse);
				lag -= elapse;
			}
			
			if (lag_render >= SecsPerRender)
			{
				lag_render -= SecsPerRender;
				renderer.Render();
				frames++;
			}
			
		}
	}

	Cleanup();
}
