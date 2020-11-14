#pragma once
#include <stdlib.h>
#include "Types.h"

class Collisions
{
public:
	static bool ExistCollision(VEC2 p1, RECT r1);
	static bool ExistCollision(RECT r1, RECT r2);	
};