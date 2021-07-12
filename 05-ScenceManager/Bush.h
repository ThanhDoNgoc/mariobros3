#pragma once
#include "GameObject.h"
#define ANI_BUSH	0
#define BUSH_WIDTH	48
#define	BUSH_HEIGHT	45
class Bush : public CGameObject
{
public:
	Bush();
	virtual void Render();
	virtual void TakeDamage() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

