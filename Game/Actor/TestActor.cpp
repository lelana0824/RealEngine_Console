#include "TestActor.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include <iostream>

TestActor::TestActor()
	:super('T', Wanted::Vector2(31,3))
{

}

void TestActor::BeginPlay()
{
	super::BeginPlay();

}

void TestActor::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	//// ESC 키 눌리면 종료
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// todo: game엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	if (Wanted::Input::Get().GetKey('D')
		&& GetPosition().x >= 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x += 1;
		SetPosition(newPosition);
	}

	if (Wanted::Input::Get().GetKey('A')
		&& GetPosition().x >= 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);
	}

	if (Wanted::Input::Get().GetKey('W')
		&& GetPosition().y >= 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);
	}

	if (Wanted::Input::Get().GetKey('S')
		&& GetPosition().y >= 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.y += 1;
		SetPosition(newPosition);
	}


	/*std::cout << "TestActor::Tick(). deltaTime: "
		<< deltaTime << ", FPS: " << (1.0f / deltaTime)
		<< "\n";*/
}

void TestActor::Draw()
{
	super::Draw();
}
