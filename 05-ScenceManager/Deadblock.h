#pragma once
#include "GameObject.h"
class Deadblock : public CGameObject
{
	int dbWidth, dbHeight;
public:
	Deadblock(int width, int height);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
};

