#include "MiniginPCH.h"
#include "Logger.h"


void PrintColor(TextColor color, std::string text)
{
	//print according to the collorcode
	printf("%c[%dm", 0x1B, (int)color);
	std::cout << text;
	printf("%c[%dm", 0x1B, (int)TextColor::DEFAULT);
	std::cout << std::endl;
	std::cout.flush();
}
