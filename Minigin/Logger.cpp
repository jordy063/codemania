#include "MiniginPCH.h"
#include "Logger.h"


void PrintColor(TextColor color, std::string text)
{
	printf("%c[%dm", 0x1B, (int)color);
	std::cout << text;
	printf("%c[%dm", 0x1B, (int)TextColor::DEFAULT);
	std::cout << std::endl;
	std::cout.flush();
}
