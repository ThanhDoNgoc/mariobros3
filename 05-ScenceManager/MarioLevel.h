#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "defineMario.h"

class MarioLevel
{
public:
	float width, height;
	MarioLevel() {};
	virtual void LevelDown() {};
	virtual void Attack() {};
};

