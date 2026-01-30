#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

#include <iostream>

Player::Player()
	:super('P', Wanted::Vector2(5,3), Wanted::Color::Red)
{

}

void Player::BeginPlay()
{
	super::BeginPlay();
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	//// 종료 키
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// todo: game엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	// 스페이스로 박스 생성
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		if (owner)
		{
			owner->AddNewActor(new Box(GetPosition()));
		}
	}

	if (Wanted::Input::Get().GetKey('D')
		&& GetPosition().x < 20)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x += 1;
		SetPosition(newPosition);
	}

	if (Wanted::Input::Get().GetKey('A')
		&& GetPosition().x > 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);
	}

	if (Wanted::Input::Get().GetKey('W')
		&& GetPosition().y > 0)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);
	}

	if (Wanted::Input::Get().GetKey('S')
		&& GetPosition().y < 15)
	{
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.y += 1;
		SetPosition(newPosition);
	}

}

void Player::Draw()
{
	super::Draw();
}
