#include "Actor.h"
#include "Util/Util.h"
#include "Core/Renderer.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Actor::Actor(const char image, const Vector2& position, Color color)
		:image(image),
		position(position),
		color(color)
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::BeginPlay()
	{
		hasBeganPlay = true;
	}
	void Actor::Tick(float deltaTime)
	{
	}
	void Actor::Draw()
	{
		Renderer::Draw(position, color, image);
	}
	void Actor::SetPosition(const Vector2& newPosition)
	{
		Renderer::Draw(position, ' ');

		// 새로운 위치 설정
		position = newPosition;
	}
}

