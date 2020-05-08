#pragma once
#include "structs.h"
#include <string>
#include <map>
class Menu
{
public:
	Menu(float2 position);
	void readDataFromJSON();
	
private:
	float2 m_Position;
	std::string m_Filename;
	std::map<std::string, std::string> m_MenuMap;

	bool readLanguageParameters(const std::string& line, const std::string& languagee);
	void makeGameObject();
};

