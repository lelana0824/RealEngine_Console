#pragma once
#include "Common/Common.h"

namespace Wanted
{
	class Input;
	class Level;

	// Main game engine class;
	class WANTED_API Engine
	{
		// 엔진 설정 구조체.
		struct EngineSetting
		{
			// 프레임 속도
			float framerate = 0.0f;
			
		};



	public:
		Engine();
		~Engine();

		// engine loop (game loop);
		void Run();
		void QuitEngine();
		// add new level;
		void SetNewLevel(class Level* newLevel);

		static Engine& Get();

	private:
		// 설정파일 로드 함수
		void LoadSetting();

		// start game play
		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();

	private:
		// engine out flag;
		bool isQuit = false;

		// 엔진 설정 값.
		EngineSetting setting;

		// 입력 관리자
		Input* input = nullptr;
	
		// main level
		class Level* mainLevel = nullptr;

		static Engine* instance;
	};
}


