#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  48
#define COIN_BBOX_HEIGHT 48

#define ANI_COIN	0;

class Coin:public CGameObject
{
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
public:
	Coin();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void TakeDamage() {};
};

