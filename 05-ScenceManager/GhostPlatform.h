#pragma once
#include "GameObject.h"
class GhostPlatform : public CGameObject
{
	int platformWidth, platformHeight;
public:
	GhostPlatform(int width, int height);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
};

