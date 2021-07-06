#pragma once
#include "GameObject.h"

class PSPortal :public CGameObject
{
	int width, height;
public:
	PSPortal(int psWidth, int psHeight);
	float camT, camL, camR, camB;
	bool isStatic, isFolow, scrollX, scrollY;
	float posX, posY;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
	virtual void InstanceDead() {};
};

