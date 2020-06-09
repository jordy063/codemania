#include "MiniginPCH.h"
#include "Menu.h"
#include <fstream>
#include "Font.h"
#include <SDL.h>
#include "InputManager.h"
#include "InputBaseObserver.h"
#include "GameObject.h"


void Menu::readDataFromJSON()
{
	//open file
    std::ifstream myfile;
    myfile.open("../Graphics/JSON.txt");
    if (myfile.fail())
    {
        std::cout << "could not find JSON file" << std::endl;
    }


    else if (myfile.is_open())
    {
        //read file and set all the parameters according to the language

        //first line is language.

        //skip 2nd line
        //read if the first parameter = language. if not next line
        //else read all parameters
        std::string line;
        int index{};
        std::string language{};
        while (std::getline(myfile, line))
        {
            switch (index)
            {
            case 0:
                language = line;
                index++;
                break;
            case 1:
                index++;
                break;
            default:
                if (readLanguageParameters(line, language))
                {
                    myfile.close();
                }


                //here we read all parameters

                break;
            }
            if (index == 0)
            {
                language = line;
                index++;
            }
            if (index == 0)
            {
                language = line;
                index++;
            }

        }
    }
}

void Menu::Initialize()
{
    readDataFromJSON();
    m_pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
    dae::ResourceManager::GetInstance().LoadTexture("../Graphics/title.png");
    m_pTitleTexture = dae::ResourceManager::GetInstance().GetTexture("../Graphics/title.png");
 
    FillInTexture(m_pMenuTextures, { 255,255,255 });
    FillInTexture(m_pSelectedMenuTextures, { 0,255,0 });
  


    m_pMenuObserver = std::make_shared<MenuObserver>(-1);
    dae::InputManager::GetInstance().Register(m_pMenuObserver, -1);
}

void Menu::Update()
{
    dae::InputManager().GetInstance().ProcessInput();

}

void Menu::Render()
{
    auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();

    

    SDL_RenderClear(renderer);
    RenderTexture(m_pTitleTexture, { 0,0 }, { 100,0 }, { 400,200 });
    RenderMenuItems();
   
    
    SDL_RenderPresent(renderer);


}

void Menu::SetShowMenu(bool showMenu)
{
    m_ShowMenu = showMenu;
}

void Menu::MoveUp()
{
    m_SelectIndex += buttonAmount - 1;
    m_SelectIndex %= buttonAmount;
}

void Menu::MoveDown()
{
    m_SelectIndex++;
    m_SelectIndex %= buttonAmount;
}

void Menu::Confirm()
{
    if (dae::InputManager().GetInstance().GetGameState() == dae::GameState::MainMenu)
    {
        //get the item by selectindex
        MenuItem action = static_cast<MenuItem>(m_SelectIndex);

        switch (action)
        {
        case MenuItem::P1PLAY:
            m_pPlayer->Clear();
            m_GameMode = GameMode::SINGLEPLAYER;
            dae::InputManager::GetInstance().SetGameState(dae::GameState::Playing);
            break;
        case MenuItem::P2PLAY:
            m_GameMode = GameMode::MULTIPLAYER;
            dae::InputManager::GetInstance().SetGameState(dae::GameState::Playing);
            break;
        case MenuItem::P2VERSUS:
            m_GameMode = GameMode::VERSUS;
            dae::InputManager::GetInstance().SetGameState(dae::GameState::Playing);
            break;


        case MenuItem::QUIT:
            m_IsQuitCalled = true;
            break;
        default:
            break;
        }
    }

    
}

void Menu::RegisterPlayer2(std::shared_ptr<dae::GameObject> pPlayer)
{
    m_pPlayer = pPlayer;
}

void Menu::CheckChangeControllers()
{
    if(m_SelectIndex == buttonAmount - 1)
    m_UseControllers = !m_UseControllers;
}

bool Menu::readLanguageParameters(const std::string& line,const std::string& language )
{
    size_t startIndex = line.find_first_of("\"", 0);

    //read ID
    size_t endIndex = line.find_first_of("\"", startIndex + 1);

    std::string readLanguage = line.substr(startIndex + 1, endIndex - startIndex - 1);
    if (readLanguage == language)
    {
        for (int i{}; i <= MenuItem::CONTROLLERSON; ++i)
        {
            startIndex = endIndex + 1;

            //read first part
            startIndex = line.find_first_of("\"", startIndex);
            endIndex = line.find_first_of("\"", startIndex + 1);
            std::string name = line.substr(startIndex + 1, endIndex - startIndex - 1);

            //read 2nd part
            startIndex = endIndex + 1;

            startIndex = line.find_first_of("\"", startIndex);
            endIndex = line.find_first_of("\"", startIndex + 1);
            std::string title = line.substr(startIndex + 1, endIndex - startIndex - 1);

            m_MenuMap[static_cast <MenuItem>(i)] = title;
        }


        return true;

    }
    return false;
     
}

void Menu::makeGameObject()
{
    //here we can make a texture component for the title
    //we can also place the fonts with the data we've read
}

void Menu::FillInTexture(std::map<MenuItem, std::shared_ptr<dae::Texture2D>>& menuTextures,SDL_Color color)
{
    for (std::pair<MenuItem, std::string> menuItem : m_MenuMap)
    {
        //const SDL_Color color = { 255,255,255 }; // only white text is supported now
        const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), menuItem.second.c_str(), color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
        }
        auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }
        SDL_FreeSurface(surf);

        menuTextures[menuItem.first] = std::make_shared<dae::Texture2D>(texture);

    }
}

void Menu::RenderMenuItems()
{
    int counter{};
   
    for (int i{}; i < buttonAmount - 1; ++i)
    {
        if (counter != m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pMenuTextures[static_cast<MenuItem>(i)], 250, 32.0f * counter + 300.0f);
           
        }
        counter++;
    }

    counter = 0;
 

    for (int i{}; i < buttonAmount - 1; ++i)
    {
        if (counter == m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pSelectedMenuTextures[static_cast<MenuItem>(i)], 250, 32.0f * counter + 300.0f);
        }
        counter++;
    }
    counter = buttonAmount - 1;
   
    if (m_UseControllers == true)
    {
        if (counter == m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pSelectedMenuTextures[static_cast<MenuItem>(MenuItem::CONTROLLERSON)], 200, 32.0f * counter + 300.0f);
        }
        else
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pMenuTextures[static_cast<MenuItem>(MenuItem::CONTROLLERSON)], 200, 32.0f * counter + 300.0f);
        }
    }
    else
    {
        if (counter == m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pSelectedMenuTextures[static_cast<MenuItem>(MenuItem::CONTROLLERSOFF)], 200, 32.0f * counter + 300.0f);
        }
        else
        {
            dae::Renderer::GetInstance().RenderTexture(*m_pMenuTextures[static_cast<MenuItem>(MenuItem::CONTROLLERSOFF)], 200, 32.0f * counter + 300.0f);
        }
    }
    
   
}

void Menu::RenderTexture(std::shared_ptr<dae::Texture2D> pTexture,float2 offset,float2 pos,float2 dimensions)
{
    UNREFERENCED_PARAMETER(offset);
    if (pTexture != nullptr)
    {
        dae::Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y, dimensions.x, dimensions.y);
    }
}
