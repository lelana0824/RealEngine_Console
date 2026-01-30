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
			// 같은 위치에 다른 액터가 있는지 확인 위함
			Actor* search = nullptr;
			for (Actor* otherActor : actors)
			{
				if (actor == otherActor)
				{
					continue;
				}

				// 위치비교
				if (actor->GetPosition() == otherActor->GetPosition())
				{
					search = otherActor;
					break;
				}
			}

			// 같은 위치에 다른 액터가 없으면 그림
			if (!search)
			{
				actor->Draw();
				continue;
			}

			// 같은 위치에 다른 액터가 있는데 우선 순위가 높으면 그림.
			if (search &&
				(actor->GetSortingOrder()) > search->GetSortingOrder())
			{
				actor->Draw();
			}
		}
	}
	void Level::AddNewActor(Actor* newActor)
	{
		// 나중에 추가를 위해 임시 배열에 저장.
		addRequestedActors.emplace_back(newActor);

		// 오너십 설정.
		newActor->SetOwner(this);
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