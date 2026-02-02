#include "Target.h"

Target::Target(Vector2& position)
	: super('T', position, Color::Green)
{
	sortingOrder = 3;
}
