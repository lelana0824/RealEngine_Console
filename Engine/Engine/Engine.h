#pragma once
#include "Common/Common.h"

namespace Wanted
{
	class  Level;

	// Main game engine class;
	class WANTED_API Engine
	{
		// data.
		// 키다운, 업, 키
		struct KeyState
		{
			// 현재 키가 눌렸는지
			bool isKeyDown = false;

			// 이전에 키가 눌렸는지
			bool wasKeyDown = false;
		};

	public:
		Engine();
		~Engine();

		// engine loop (game loop);
		void Run();
		void QuitEngine();

		// 입력 확인 함수

		// 이전 입력 x, 현재 입력 o
		bool GetKeyDown(int keyCode);
		// 이전 입력 o, 현재 입력 x
		bool GetKeyUp(int keyCode);
		// 눌려있음
		bool GetKey(int keyCode);

		// add new level;
		void SetNewLevel(class Level* newLevel);

	private:
		void ProcessInput();

		// start game play
		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();

	private:
		// engine out flag;
		bool isQuit = false;
		
		// 키 상태 저장용 배열.
		KeyState keyStates[255] = {};

		// main level
		class Level* mainLevel = nullptr;
	};
}


