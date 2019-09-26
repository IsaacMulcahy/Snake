#pragma once

#include "WorldObject.h"

class Apple
{
public:
	Apple() = default;
	~Apple() = default;

	int getApple();
	bool applehit(int);

protected:
	int apple_pool[2];
	bool hit[2];
};
