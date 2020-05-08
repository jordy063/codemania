#include "MiniginPCH.h"
#include "Menu.h"
#include <fstream>

Menu::Menu(float2 position)
	:m_Position(position)
{
    readDataFromJSON();
}

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
