#pragma once
#include "GameObject.h"
#define BOOMERANG_BBOX_WIDTH	48
#define BOOMERANG_BBOX_HEIGHT	48

#define ANI_ID_BOOMERANG_FLY	0

#define BOOMERANG_FLY_SPEED	0.2f
#define BOOMERANG_FLY_SPEED_Y	0.15f
#define BOOMERANG_DISTANCE_X	336


class Boomerang : public CGameObject
{
public:
	bool canFlyBack;
	Boomerang(float posX, float posY, float direcX);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void TakeDamage();
	D3DXVECTOR2 direction = D3DXVECTOR2(1.0f, 1.0f);
};

