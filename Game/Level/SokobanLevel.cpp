#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
	//AddNewActor(new Player());
	//LoadMap("Stage1.txt");
	LoadMap("Map.txt");
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

	return false;
}
