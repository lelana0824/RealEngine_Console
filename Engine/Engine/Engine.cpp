#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	// 전역 변수 초기화
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		instance = this;

		// 입력 관리자 생성
		input = new Input();

		LoadSetting();

		// 커서 끄기
		CONSOLE_CURSOR_INFO info = {};

		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);

		info.bVisible = false;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}

	Engine::~Engine()
	{
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		if (input)
		{
			delete input;
			input = nullptr;
		}
	}

	void Engine::Run()
	{
		// 시계 정밀도
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		__int64 currentTime = 0;
		__int64 previousTime = 0;

		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		currentTime = time.QuadPart;
		previousTime = currentTime;

		// 기준 프레임 (단위초)
		//float targetFrameRate = 120.0f;
		setting.framerate
			= setting.framerate == 0.0f ? 60.0f : setting.framerate;

		float oneFrameTime = 1.0f / setting.framerate;

		while (!isQuit)
		{
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;
			
			
			// cal frame;
			float deltaTime =
				static_cast<float>(currentTime - previousTime);
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			// 고정프레임기법
			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();

				// 프레임처리
				BeginPlay();
				Tick(deltaTime);
				Draw();

				// 이전 시간 값 갱신.
				previousTime = currentTime;

				input->SavePreviousInputStates();
			}
			
		}

		// Todo: 정리작업
		std::cout << "Engine has been shutdown!!\n";
		// 커서 끄기
		CONSOLE_CURSOR_INFO info = {};

		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);

		info.bVisible = true;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		// todo: 임시 코드. 레벨 전환 시 바로 제거 x
		if (mainLevel) {
			delete mainLevel;
			mainLevel = nullptr;
		}

		// set level
		mainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		if (!instance)
		{
			std::cout << "Error: Engine:Get(). instance is null\n";
			__debugbreak();
		}
		return *instance;
	}

	void Engine::LoadSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");
		if (!file)
		{
			std::cout << "Failed to open engine setting file.\n";
			__debugbreak();
			return;
		}

		char buffer[2048] = {};

		size_t readSize = fread(buffer, sizeof(char), 2048, file);

		// 문자열 포맷 활용해서 데이터 추출.
		sscanf_s(buffer, "framerate = %f", &setting.framerate);



		fclose(file);
	}

	void Engine::BeginPlay()
	{
		// 레벨이 있으면 이벤트 전달
		if (!mainLevel) {
			std::cout << "mainLevel is empty. \n";
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		//std::cout << "DeltaTime: " << deltaTime
		//	<< ", FPS: " << (1.0f / deltaTime) << "\n";

		// event to level

		if (!mainLevel)
		{
			std::cout << "Error: Engine::Tick(). mainLevel is empty\n";
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Draw(). mainLevel is empty\n";
			return;
		}

		mainLevel->Draw();
	}
}