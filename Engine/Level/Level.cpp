#include "Level.h"
#include "Actor/Actor.h"

namespace Wanted
{
	Level::Level()
	{
	}
	Level::~Level()
	{
		// 메모리 정리
		for (Actor*& actor : actors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		// 배열 초기화
		actors.clear();
	}

	void Level::BeginPlay()
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			if (actor->HasBeganPlay()) {
				continue;
			}

			actor->BeginPlay();
		}
	}
	void Level::Tick(float deltaTime)
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}
	void Level::Draw()
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : actors)
		{
			actor->Draw();
		}
	}
	void Level::AddNewActor(Actor* newActor)
	{
		// todo: 나중에 프레임 처리 고려해서 따로 추가 작업
		//actors.emplace_back(newActor);
		addRequestedActors.emplace_back(newActor);
	}
	void Level::ProcessAddAndDestroyActors()
	{
		// 제거 처리
		for (int i = 0; i < static_cast<int>(actors.size());)
		{
			// 제거 요청된 액터가 있는지 확인
			if (actors[i]->IsDestroyRequested())
			{
				// 삭제처리
				delete actors[i];
				actors.erase(actors.begin() + i);
				continue;
			}

			++i;
		}


		// 추가 처리.
		if (addRequestedActors.size() == 0)
		{
			return;
		}

		for (Actor* const actor : addRequestedActors)
		{
			actors.emplace_back(actor);
		}

		addRequestedActors.clear();
	}
}