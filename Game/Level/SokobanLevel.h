#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Wanted::Level,
	public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)
public:
	SokobanLevel();

	virtual void Draw() override;

private:
	void LoadMap(const char* filename);

	// ICanPlayerMove을(를) 통해 상속됨
	virtual bool CanMove(const Vector2& playerPosition, const Vector2& nextPosition) override;

	// 게임 클리어 확인 함수
	bool CheckGameClear();
private:
	// 목표 점수
	int targetScore = 0;

	// 게임 클리어 여부 알려주는 변수
	bool isGameClear = false;
};

