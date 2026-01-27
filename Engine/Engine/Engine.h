#pragma once
#include "Common/Common.h"

namespace Wanted
{
	class Input;
	class Level;

	// Main game engine class;
	class WANTED_API Engine
	{
	public:
		Engine();
		~Engine();

		// engine loop (game loop);
		void Run();
		void QuitEngine();
		// add new level;
		void SetNewLevel(class Level* newLevel);

	private:
		// start game play
		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();

	private:
		// engine out flag;
		bool isQuit = false;

		// 입력 관리자
		Input* input = nullptr;
	
		// main level
		class Level* mainLevel = nullptr;
	};
}


