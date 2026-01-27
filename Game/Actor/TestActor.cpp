#include "TestActor.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include <iostream>

void TestActor::BeginPlay()
{
	Actor::BeginPlay();

	std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);


	//// ESC 키 눌리면 종료
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// todo: game엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}


	std::cout << "TestActor::Tick(). deltaTime: "
		<< deltaTime << ", FPS: " << (1.0f / deltaTime)
		<< "\n";
}

void TestActor::Draw()
{
	Actor::Draw();
}
