#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>

Player::Player(const Wanted::Vector2& position)
	:super('P', position, Wanted::Color::Red)
{
	sortingOrder = 10;
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
	//if (Input::Get().GetKeyDown(VK_SPACE))
	//{
	//	if (owner)
	//	{
	//		owner->AddNewActor(new Box(GetPosition()));
	//	}
	//}

	// 인터페이스 확인
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	if (!canPlayerMoveInterface && GetOwner())
	{
		canPlayerMoveInterface
			= dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

	if (Wanted::Input::Get().GetKeyDown('D')
		&& GetPosition().x < 20)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(
			GetPosition().x + 1, GetPosition().y
		);
		if (canPlayerMoveInterface->CanMove(
			GetPosition(),
			newPosition
		))
		{
			SetPosition(newPosition);
		}
	}

	if (Wanted::Input::Get().GetKeyDown('A')
		&& GetPosition().x > 0)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(
			GetPosition().x - 1, GetPosition().y
		);
		if (canPlayerMoveInterface->CanMove(
			GetPosition(),
			newPosition
		))
		{
			SetPosition(newPosition);
		}
	}

	if (Wanted::Input::Get().GetKeyDown('W')
		&& GetPosition().y > 0)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(
			GetPosition().x, GetPosition().y - 1
		);
		if (canPlayerMoveInterface->CanMove(
			GetPosition(),
			newPosition
		))
		{
			SetPosition(newPosition);
		}
	}

	if (Wanted::Input::Get().GetKeyDown('S')
		&& GetPosition().y < 15)
	{
		// 이동 가능 여부 판단
		Vector2 newPosition(
			GetPosition().x, GetPosition().y + 1
		);
		if (canPlayerMoveInterface->CanMove(
			GetPosition(),
			newPosition
		))
		{
			SetPosition(newPosition);
		}
	}

}

void Player::Draw()
{
	super::Draw();
}
