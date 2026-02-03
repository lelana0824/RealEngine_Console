#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;

int main()
{
	// 예시 배열.
	const int width = 3;
	const int height = 3;
	CHAR_INFO charArray[width * height] = { };

	charArray[2 * width + 1].Char.AsciiChar = 'P';
	charArray[2 * width + 1].Attributes = FOREGROUND_GREEN;

	charArray[0 * width + 1].Char.AsciiChar = '#';
	charArray[0 * width + 1].Attributes = FOREGROUND_RED;

	COORD position = {};
	COORD screenSize;
	screenSize.X = width;
	screenSize.Y = height;

	SMALL_RECT writeRegion{
		0,
		0,
		static_cast<short>(width),
		static_cast<short>(height)
	};

	WriteConsoleOutputA(
		GetStdHandle(STD_OUTPUT_HANDLE),
		charArray,
		screenSize,
		position,
		&writeRegion
	);

	/*Game game;
	game.Run();*/

	std::cin.get();
}