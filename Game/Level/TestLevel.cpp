#include "TestLevel.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	AddNewActor(new Player());
}
