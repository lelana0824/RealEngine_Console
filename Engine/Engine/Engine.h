#pragma once

namespace Wanted
{
	// Main game engine class;
	class Engine
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

	private:
		void ProcessInput();

		void Tick(float deltaTime);

		void Draw();

	private:
		// engine out flag;
		bool isQuit = false;
		
		// 키 상태 저장용 배열.
		KeyState keyStates[255] = {};
	};
}


