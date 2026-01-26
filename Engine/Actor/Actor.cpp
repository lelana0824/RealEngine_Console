#include "Actor.h"

namespace Wanted
{
	Actor::Actor()
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
	}
}

