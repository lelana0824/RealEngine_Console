#pragma once
#include "Actor\Actor.h"

using namespace Wanted;

class Target :
    public Actor
{
    RTTI_DECLARATIONS(Target, Actor)
public:
    Target(Vector2& position);
};

