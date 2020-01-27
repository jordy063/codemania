#pragma once
#include <string>
#include <iostream>
enum TextColor
{
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE=34,
	MAGENTA = 35,
	CYAN = 36,
	WHITE = 37,
	DEFAULT = 39
};

void PrintColor(TextColor color, std::string text);
