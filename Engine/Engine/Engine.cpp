#include "Engine.h"
#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Engine::Engine()
	{

	}

	Engine::~Engine()
	{
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
		float targetFrameRate = 120.0f;
		float oneFrameTime = 1.0f / targetFrameRate;

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
				ProcessInput();

				// 프레임처리
				Tick(deltaTime);
				Draw();

				// 이전 시간 값 갱신.
				previousTime = currentTime;

				// 현재 입력 값을 이전 입력 값으로 저장
				// 키 마다의 입력 읽기.
				// 운영체제가 제공하는 기능을 사용할수 밖에 없음.
				for (int i = 0; i < 255; i++)
				{
					keyStates[i].wasKeyDown = keyStates[i].isKeyDown;
				}
			}
			
		}

		// Todo: 정리작업
		std::cout << "Engine has been shutdown!!\n";
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	bool Engine::GetKeyDown(int keyCode)
	{
		return keyStates[keyCode].isKeyDown &&
			!keyStates[keyCode].wasKeyDown;
	}

	bool Engine::GetKeyUp(int keyCode)
	{
		return !keyStates[keyCode].isKeyDown &&
			keyStates[keyCode].wasKeyDown;;
	}

	bool Engine::GetKey(int keyCode)
	{
		return keyStates[keyCode].isKeyDown;
	}

	void Engine::ProcessInput()
	{
		// 키 마다의 입력 읽기.
		// 운영체제가 제공하는 기능을 사용할수 밖에 없음.
		for (int i = 0; i < 255; i++)
		{
			keyStates[i].isKeyDown
				= (GetAsyncKeyState(i) & 0x8000) > 0 ? true : false;
		}
	}

	void Engine::Tick(float deltaTime)
	{
		std::cout << "DeltaTime: " << deltaTime
			<< ", FPS: " << (1.0f / deltaTime) << "\n";

		// ESC 키 눌리면 종료
		if (GetKeyDown(VK_ESCAPE))
		{
			QuitEngine();
		}
	}

	void Engine::Draw()
	{
	}
}