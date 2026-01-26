#pragma once
#include <vector>

namespace Wanted {
	class Actor;

	// 담당임무: 레벨에 있는 모든 액터 관리.
	class Level
	{
	public:
		Level();
		virtual ~Level();

		// 게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

	protected:
		std::vector<Actor*> actors;
	};

}

