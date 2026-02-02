#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Util/Util.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
	//AddNewActor(new Player());
	//LoadMap("Stage1.txt");
	LoadMap("Map.txt");
}

void SokobanLevel::Draw()
{
	super::Draw();

	if (CheckGameClear())
	{
		// 콘솔 위치/색상 설정.
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// 게임 클리어 메시지
		std::cout << "Game Clear!\n";
	}
}

void SokobanLevel::LoadMap(const char* filename)
{
	// 최종 파일 경로 만들기.
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외처리
	if (!file)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file \n";
		__debugbreak();
		return;
	}

	// 맵 읽기.
	// 맵 크기 파악: FP 포인터를 파일의 끝으로 이동
	fseek(file, 0, SEEK_END);

	// 위치 읽기
	size_t fileSize = ftell(file);

	// fp 처음으로 되돌리기
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성
	char* data = new char[fileSize + 1];

	// 데이터 읽기
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석(파싱)해서 출력
	// 인덱스를 사용해서 한문자씩 읽기
	int index = 0;

	// 객체를 생성할 위치값
	Wanted::Vector2 position;

	while (true)
	{
		if (index >= fileSize)
		{
			break;
		}

		char mapCharacter = data[index];
		++index;

		// 개행문자처리
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}


		/*
		#: 벽(Wall)
		.: 바닥(Ground)
		p: 플레이어(Player)
		b: 박스(Box)
		t: 타겟(Target)
		*/

		switch (mapCharacter)
		{
		case '#':
		case '1':
			AddNewActor(new Wall(position));
			break;

		case '.':
			AddNewActor(new Ground(position));
			break;
			
		case 'p':
			AddNewActor(new Player(position));
			AddNewActor(new Ground(position));
			break;

		case 'b':
			// 박스가 옮겨졌을때 그 밑에 땅이 있어야 함.
			AddNewActor(new Box(position));
			AddNewActor(new Ground(position));
			break;

		case 't':
			AddNewActor(new Target(position));
			++targetScore;
			break;
		}

		// x 좌표 증가처리
		++position.x;
	}

	delete[] data;
	fclose(file);
}

bool SokobanLevel::CanMove(
	const Vector2& playerPosition,
	const Vector2& nextPosition)
{
	// 레벨에 있는 박스 액터 모으기.
	// 박스는 플레이어가 밀기 등 추가적으로 처리해야하기 때문.
	std::vector<Actor*> boxes;
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인
	Actor* boxActor = nullptr;
	for (Actor* const box : boxes)
	{
		// 위치 비교
		if (box->GetPosition() == nextPosition)
		{
			boxActor = box;
			break;
		}
	}

	// 경우의 수 처리
	// 이동하려는 곳에 박스가 있는 경우
	if (boxActor)
	{
		// #1: 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인
		// 두 위치 사이에서 이동 방향 구하기 (벡터의 뻴셈 활용).
		Vector2 direction = nextPosition - playerPosition;
		Vector2 newPosition = boxActor->GetPosition() + direction;

		// 검색
		for (Actor* const otherBox : boxes)
		{
			if (otherBox == boxActor)
			{
				continue;
			}

			// 다른 박스가 있는지 확인
			if (otherBox->GetPosition() == newPosition)
			{
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == newPosition)
			{
				// #2: 벽이면 이동 불가.
				if (actor->IsTypeOf<Wall>())
				{
					return false;
				}

				// #3: 그라운드 또는 타겟이면 이동 가능.
				if (actor->IsTypeOf<Ground>()
					|| actor->IsTypeOf<Target>())
				{
					// 박스 이동 처리
					boxActor->SetPosition(newPosition);

					// 게임 점수 확인.
					isGameClear = CheckGameClear();

					return true;
				}
			}
		}
	}


	// 이동하려는 곳에 박스가 없는 경우.
	// 이동하려는 곳에 있는 액터가 벽이 아니면 이동 가능
	for (Actor* const actor : actors)
	{
		if (actor->GetPosition() == nextPosition)
		{
			// 이 액터가 벽인지 확인.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}

			return true;
		}
	}

	return false;
}

bool SokobanLevel::CheckGameClear()
{
	// 타겟 위에 있는 박스의 수 검증.

	int currentScore = 0;

	// 동적배열에 박스 및 타겟 저장.
	std::vector<Actor*> boxes;
	std::vector<Actor*> targets;

	// 레벨에 배치된 배열 순회하면서 두 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}

		if (actor->IsTypeOf<Target>())
		{
			targets.emplace_back(actor);
			continue;
		}
	}

	// 점수 확인 (박스의 위치 == 타겟의 위치)
	for (Actor* const box : boxes)
	{
		for (Actor* const target : targets)
		{
			if (box->GetPosition() == target->GetPosition())
			{
				currentScore += 1;
			}
		}
	}

	return currentScore == targetScore;
}
