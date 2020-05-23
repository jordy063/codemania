#include "MiniginPCH.h"
#include "Menu.h"
#include <fstream>
#include "Font.h"
#include <SDL.h>
#include "InputManager.h"
#include "InputBaseObserver.h"


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

    for (std::pair<std::string, std::string> menuItem : m_MenuMap)
    {
        //const SDL_Color color = { 255,255,255 }; // only white text is supported now
        const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), menuItem.second.c_str(), { 255,255,255 });
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
        m_pMenuTextures[menuItem.first] = std::make_shared<dae::Texture2D>(texture);

    }

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

    int counter{};
    for (std::pair<const std::string, std::shared_ptr<dae::Texture2D>> menuTextures : m_pMenuTextures)
    {
        if (counter == m_SelectIndex)
        {
            dae::Renderer::GetInstance().RenderTexture(*menuTextures.second, 132.0f, 32.0f * counter+100.0f);
        }
        else
        {
            dae::Renderer::GetInstance().RenderTexture(*menuTextures.second, 100.0f, 32.0f * counter + 100.0f);
        }

        counter++;
    }
    
    SDL_RenderPresent(renderer);


}

void Menu::SetShowMenu(bool showMenu)
{
    m_ShowMenu = showMenu;
}

void Menu::MoveUp()
{
    m_SelectIndex++;
    m_SelectIndex %= m_MenuMap.size();
}

void Menu::MoveDown()
{
    m_SelectIndex--;
    m_SelectIndex %= m_MenuMap.size();
}

void Menu::Confirm()
{
    //get the item by selectindex
    //uto action = 
    SetShowMenu(false);
}

bool Menu::readLanguageParameters(const std::string& line,const std::string& language )
{
    size_t startIndex = line.find_first_of("\"", 0);

    //read ID
    size_t endIndex = line.find_first_of("\"", startIndex + 1);

    std::string readLanguage = line.substr(startIndex + 1, endIndex - startIndex - 1);
    if (readLanguage == language)
    {
        //FIRST PARAMETER
        startIndex = endIndex + 1;

        //read first part
        startIndex = line.find_first_of("\"", startIndex);
        endIndex = line.find_first_of("\"", startIndex + 1);
        std::string gameStart = line.substr(startIndex + 1, endIndex - startIndex - 1);

        //read 2nd part
        startIndex = endIndex + 1;

        startIndex = line.find_first_of("\"", startIndex);
        endIndex = line.find_first_of("\"", startIndex + 1);
        std::string start = line.substr(startIndex + 1, endIndex - startIndex - 1);

        m_MenuMap[gameStart] = start;

        //2ND PARAMETER
        startIndex = endIndex + 1;

        //read first part
        startIndex = line.find_first_of("\"", startIndex);
        endIndex = line.find_first_of("\"", startIndex + 1);
        std::string gameQuit = line.substr(startIndex + 1, endIndex - startIndex - 1);

        //read 2nd part
        startIndex = endIndex + 1;

        startIndex = line.find_first_of("\"", startIndex);
        endIndex = line.find_first_of("\"", startIndex + 1);
        std::string quit = line.substr(startIndex + 1, endIndex - startIndex - 1);

        m_MenuMap[gameQuit] = quit;

        return true;

    }
    return false;
     
}

void Menu::makeGameObject()
{
    //here we can make a texture component for the title
    //we can also place the fonts with the data we've read
}
