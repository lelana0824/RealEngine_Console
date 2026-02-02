#pragma once
#include "Level/Level.h"

class TestLevel : public Wanted::Level
{
	RTTI_DECLARATIONS(TestLevel, Level)
public:
	TestLevel();

private:
	void LoadMap(const char* filename);
};

