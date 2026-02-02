#pragma once

#include "Math/Vector2.h"

using namespace Wanted;

// 플레이어가 이동할 위치를 판단해주는 인터페이스.
// Cpp 인터페이스 = 순수 가상함수를 가지는 클래스.
class ICanPlayerMove
{
public:
	virtual bool CanMove(
		const Vector2& playerPosition,
		const Vector2& nextPosition
	) = 0;
};